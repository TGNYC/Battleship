//
// Created by Tejas Gupta on 4/19/23.
//

#include "server_network_manager.h"

#include "network/responses/ServerResponse.h"
#include "request_handler.h"
#include "serialization/serialization.h"
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include "Logger.h"

// Constructor of server_network_manager
server_network_manager::server_network_manager(const uint16_t port) : _port(port) {
  // Initialize the sockpp library
  sockpp::socket_initializer::initialize();
  // Connect to the default server host and port, as defined in "default.conf"
  this->connect(port);
}

// Destructor of server_network_manager
server_network_manager::~server_network_manager() = default;

// Connect to a specified url and port using a tcp_acceptor
void server_network_manager::connect(const uint16_t port) {
  // Create a tcp_acceptor using the specified port
  this->_acc = sockpp::tcp_acceptor(port);

  // Check if the acceptor was created successfully
  if (!_acc) {
    std::cerr << "Error creating the acceptor: " << _acc.last_error_str() << std::endl;
    return;
  }

  // Print a message indicating that the server is awaiting connections on the specified port
  LOG("Awaiting connections on port " + std::to_string(port) + "...");

  // Start an endless loop that listens for incoming connections and reads incoming messages
  // this->listener_loop();
}

// Endless loop that listens for incoming connections and reads incoming messages
void server_network_manager::listener_loop() {
  // Intentional endless loop
  while (true) {
    // Accept a new client connection
    sockpp::inet_address peer;
    sockpp::tcp_socket   sock = _acc.accept(&peer);

    // Print a message indicating that a connection was received from the specified peer
    LOG("Received a connection request from " + peer.to_string());

    // Check if the socket was created successfully
    if (!sock) {
      std::cerr << "Error accepting incoming connection: " << _acc.last_error_str() << std::endl;
    } else {
      LOG("Socket created successfully");
      // Add the socket to a map, and create a new thread to handle incoming messages
      _rw_lock.lock();
      _address_to_socket.emplace(sock.peer_address().to_string(), std::move(sock.clone()));
      _rw_lock.unlock();
      std::thread listener(read_message, std::move(sock),
                           [this](const std::string &message, const sockpp::tcp_socket::addr_t &address) {
                             this->handle_message(message, address);
                           });
      listener.detach();
    }
  }
}

// Runs in a thread and reads anything coming in on the 'socket'.
// Once a message is fully received, the string is passed on to the 'handle_message()' function
void server_network_manager::read_message(
    sockpp::tcp_socket socket,
    const std::function<void(const std::string &, const sockpp::tcp_socket::addr_t &)> &message_handler) {
  // sockpp::socket_initializer sockInit; // initializes socket framework underneath
  LOG("Reading message");
  char    buffer[512]; // 512 bytes
  ssize_t count          = 0;
  ssize_t msg_bytes_read = 0;
  ssize_t msg_length     = 0;

  while ((count = socket.read(buffer, sizeof(buffer))) > 0) {
    try {
      int               i = 0;
      std::stringstream ss_msg_length;
      while (buffer[i] != ':' && i < count) {
        ss_msg_length << buffer[i];
        i++;
      }
      msg_length = std::stoi(ss_msg_length.str());
      LOG("Expecting message of length " + std::to_string(msg_length));

      // put everything after the message length declaration into a stringstream
      std::stringstream ss_msg;
      ss_msg.write(&buffer[i + 1], count - (i + 1));
      msg_bytes_read = count - (i + 1);

      // read the remaining packages
      while (msg_bytes_read < msg_length && count > 0) {
        count          = socket.read(buffer, sizeof(buffer));
        msg_bytes_read += count;
        ss_msg.write(buffer, count);
      }

      if (msg_bytes_read == msg_length) {
        // sanity check that really all bytes got read (possibility that count was <= 0, indicating a read error)
        std::string msg = ss_msg.str();
        LOG("About to parse client_request");
        message_handler(msg, socket.peer_address()); // attempt to parse client_request from 'msg'
      } else {
        std::cerr << "Could not read entire message. TCP stream ended before. Difference is "
                  << msg_length - msg_bytes_read << std::endl;
      }
    } catch (std::exception &e) { // Make sure the connection isn't torn down only because of a read error
      std::cerr << "Error while reading message from " << socket.peer_address() << std::endl << e.what() << std::endl;
    }
  }
  LOG("Value of count: " + std::to_string(count));

  if (count <= 0) {
    LOG("Didn't get to read anything from the buffer");
    LOG("Read error [" + std::to_string(socket.last_error()) + "]: " + socket.last_error_str());
  }

  LOG("Closing connection to " + socket.peer_address().to_string());
  socket.shutdown();
}

void server_network_manager::handle_message(const std::string                &msg,
                                                     const sockpp::tcp_socket::addr_t &peer_address) {
  try {
    LOG("Handling the incoming message");
    // try to parse a json from the 'msg'
    nlohmann::json                       req_json = nlohmann::json::parse(msg);
    const std::unique_ptr<ClientRequest> req      = req_json;

    // check if this is a connection to a new player
    uuid player_id = req->getPlayerId();
    _rw_lock.lock_shared();
    if (_player_id_to_address.find(player_id) == _player_id_to_address.end()) {
      // save connection to this client
      _rw_lock.unlock_shared();
      LOG("New client with id " + player_id.ToString());
      _rw_lock.lock();
      _player_id_to_address.emplace(player_id, peer_address.to_string());
      _rw_lock.unlock();
    } else {
      _rw_lock.unlock_shared();
    }
#ifdef PRINT_NETWORK_MESSAGES
    LOG("Received valid request : " + msg);
#endif
    // -- handle client request and create response
    const std::unique_ptr<ServerResponse> res = request_handler::handle_request(_game_instance, req.get());

    // res == nullptr if request does not require personal response. e.g. when already broadcasted to both
    if (res != nullptr) {
      // transform response into a json
      nlohmann::json res_json = *res;
      // transform json to string
      const std::string res_msg = res_json.dump();
      LOG("Response message: " + res_msg);
      // send response back to client
      send_message(res_msg, peer_address.to_string());
    }
  } catch (const std::exception &e) {
    std::cerr << "Failed to execute client request. Content was :\n"
              << msg << std::endl
              << "Error was " << e.what() << std::endl;
  }
}

void server_network_manager::on_player_left(uuid player_id) {
  _rw_lock.lock();
  const std::string address = _player_id_to_address[player_id];
  _player_id_to_address.erase(player_id);
  _address_to_socket.erase(address);
  _rw_lock.unlock();
}

ssize_t server_network_manager::send_message(const std::string &msg, const std::string &address) {
  std::stringstream ss_msg;
  ss_msg << std::to_string(msg.size()) << ':' << msg; // prepend message length
  return _address_to_socket.at(address).write(ss_msg.str());
}

void server_network_manager::broadcast_message(ServerResponse &msg, const std::vector<Player> &players,
                                               const Player *exclude) {
  nlohmann::json msg_json   = msg;             // write to JSON format
  std::string    msg_string = msg_json.dump(); // convert to string

#ifdef PRINT_NETWORK_MESSAGES
  std::cout << "Broadcasting message : " << msg_string << std::endl;
#endif

  _rw_lock.lock_shared();
  // send object_diff to all requested players
  try {
    for (auto &player : players) {
      if (exclude == nullptr || player != *exclude) {
        ssize_t nof_bytes_written = send_message(msg_string, _player_id_to_address.at(player.getId()));
        LOG("number of bytes written: " + std::to_string(nof_bytes_written));
      }
    }
  } catch (std::exception &e) {
    std::cerr << "Encountered error when sending state update: " << e.what() << std::endl;
  }
  _rw_lock.unlock_shared();
}
