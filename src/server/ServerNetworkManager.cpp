//
// Created by Tejas Gupta on 4/19/23.
//

#include "ServerNetworkManager.h"

#include "Logger.h"
#include "RequestHandler.h"
#include "network/responses/ServerResponse.h"
#include "serialization/serialization.h"
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

// Constructor of server_network_manager
ServerNetworkManager::ServerNetworkManager(const uint16_t port) : _port(port) {
  // Initialize the sockpp library
  sockpp::socket_initializer::initialize();
  // Connect to the default server host and port, as defined in "default.conf"
  this->connect(port);
}

// Destructor of server_network_manager
ServerNetworkManager::~ServerNetworkManager() = default;

// Connect to a specified url and port using a tcp_acceptor
void ServerNetworkManager::connect(const uint16_t port) {
  // Create a tcp_acceptor using the specified port
  this->_acc = sockpp::tcp_acceptor(port);

  // Check if the acceptor was created successfully
  if (!_acc) {
    std::cerr << "Error creating the acceptor: " << _acc.last_error_str() << std::endl;
    return;
  }
  // Print a message indicating that the server is awaiting connections on the specified port // TODO also print ip
  LOG("Awaiting connections on port " + std::to_string(port) + "...");
}

// Endless loop that listens for incoming connections and reads incoming messages
void ServerNetworkManager::listenerLoop() {
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
      _rwLock.lock();
      _addressToSocket.emplace(sock.peer_address().to_string(), sock.clone());
      _rwLock.unlock();
      std::thread listener(readMessage, std::move(sock),
                           [this](const std::string &message, const sockpp::tcp_socket::addr_t &address) {
                             this->handleMessage(message, address);
                           });
      listener.detach();
    }
  }
}

// Runs in a thread and reads anything coming in on the 'socket'.
// Once a message is fully received, the string is passed on to the 'handle_message()' function
void ServerNetworkManager::readMessage(
    sockpp::tcp_socket                                                                  socket,
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
  if (count <= 0) {
    LOG("Didn't get to read anything from the buffer");
    LOG("Read error [" + std::to_string(socket.last_error()) + "]: " + socket.last_error_str());
  }
  LOG("Closing connection to " + socket.peer_address().to_string());
  socket.shutdown();
}

void ServerNetworkManager::handleMessage(const std::string &msg, const sockpp::tcp_socket::addr_t &peer_address) {
  try {
    LOG("handling incoming message");
    // try to parse a json from the 'msg'
    nlohmann::json                       req_json = nlohmann::json::parse(msg);
    const std::unique_ptr<ClientRequest> req      = req_json;

    // check if this is a connection to a new player
    uuid player_id = req->getPlayerId();
    _rwLock.lock_shared();
    if (_playerIdToAddress.find(player_id) == _playerIdToAddress.end()) {
      // save connection to this client
      _rwLock.unlock_shared();
      LOG("new client with id " + player_id.ToString());
      _rwLock.lock();
      _playerIdToAddress.emplace(player_id, peer_address.to_string());
      _rwLock.unlock();
    } else {
      _rwLock.unlock_shared();
    }

    // -- handle client request and create response
    const std::unique_ptr<ServerResponse> res = RequestHandler::handleRequest(_gameInstance, req.get());

    // res == nullptr if request does not require personal response. e.g. when already broadcasted to both
    if (res != nullptr) {
      // transform response into a json
      nlohmann::json res_json = *res;
      // transform json to string
      const std::string res_msg = res_json.dump();
      LOG("Response message: " + res_msg);
      // send response back to client
      sendMessage(res_msg, peer_address.to_string());
    }
  } catch (const std::exception &e) {
    std::cerr << "Failed to execute client request. Content was :\n"
              << msg << std::endl
              << "Error was " << e.what() << std::endl;
  }
}

void ServerNetworkManager::on_player_left(uuid player_id) {
  _rwLock.lock();
  const std::string address = _playerIdToAddress[player_id];
  _playerIdToAddress.erase(player_id);
  _addressToSocket.erase(address);
  _rwLock.unlock();
}

ssize_t ServerNetworkManager::sendMessage(const std::string &msg, const std::string &address) {
  std::stringstream ss_msg;
  ss_msg << std::to_string(msg.size()) << ':' << msg; // prepend message length
  return _addressToSocket.at(address).write(ss_msg.str());
}

void ServerNetworkManager::broadcastMessage(ServerResponse &msg, const std::vector<Player> &players,
                                            const Player *exclude) {
  nlohmann::json msg_json   = msg;             // write to JSON format
  std::string    msg_string = msg_json.dump(); // convert to string

#ifdef PRINT_NETWORK_MESSAGES
  std::cout << "Broadcasting message : " << msg_string << std::endl;
#endif

  _rwLock.lock_shared();
  // send object_diff to all requested players
  try {
    for (auto &player : players) {
      if (exclude == nullptr || player != *exclude) {
        ssize_t nof_bytes_written = sendMessage(msg_string, _playerIdToAddress.at(player.getId()));
        LOG("number of bytes written: " + std::to_string(nof_bytes_written));
      }
    }
  } catch (std::exception &e) {
    std::cerr << "Encountered error when sending state update: " << e.what() << std::endl;
  }
  _rwLock.unlock_shared();
}
