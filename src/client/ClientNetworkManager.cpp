#include "ClientNetworkManager.h"

#include "GameController.h"
#include "Logger.h"
#include "ResponseListenerThread.h"
#include "serialization/serialization.h"
#include <nlohmann/json.hpp>
#include <sockpp/exception.h>
#include <sockpp/tcp_connector.h>
#include <sstream>

// initialize static members
sockpp::tcp_connector  *ClientNetworkManager::_connection             = nullptr;
ResponseListenerThread *ClientNetworkManager::_responseListenerThread = nullptr;

bool ClientNetworkManager::_connectionSuccess = false;
bool ClientNetworkManager::_failedToConnect   = false;

void ::ClientNetworkManager::init(const std::string &host, const uint16_t port) {

  LOG("ClientNetworkManager init");

  // initialize sockpp framework
  sockpp::initialize();

  // reset connection status
  ClientNetworkManager::_connectionSuccess = false;
  ClientNetworkManager::_failedToConnect   = false;

  // delete exiting connection and create new one
  if (ClientNetworkManager::_connection != nullptr) {
    ClientNetworkManager::_connection->shutdown();
    if (_responseListenerThread != nullptr) {
      _responseListenerThread->Delete();
      _responseListenerThread = nullptr;
    }
    delete ClientNetworkManager::_connection;
  }
  ClientNetworkManager::_connection = new sockpp::tcp_connector();

  // try to connect to server
  if (ClientNetworkManager::connect(host, port)) {
    ClientNetworkManager::_connectionSuccess = true;
    LOG("successfully connected to server");
    // start network thread
    _responseListenerThread = new ResponseListenerThread(ClientNetworkManager::_connection);
    if (_responseListenerThread->Run() != wxTHREAD_NO_ERROR) {
      GameController::showError("connection error", "Could not create client network thread", false);
    }
  } else {
    ClientNetworkManager::_failedToConnect = true;
    LOG("connection error");
  }
}

bool ClientNetworkManager::connect(const std::string &host, const uint16_t port) {

  // create sockpp address and catch any errors
  sockpp::inet_address address;
  try {
    address = sockpp::inet_address(host, port);
  } catch (const sockpp::getaddrinfo_error &e) {
    GameController::showError("Connection error", "Failed to resolve address " + e.hostname(), true);
    return false;
  }

  // establish connection to given address
  if (!ClientNetworkManager::_connection->connect(address)) {
    GameController::showError("Connection error", "Failed to connect to server " + address.to_string(), true);
    return false;
  }

  return true;
}

void ClientNetworkManager::sendRequest(const ClientRequest &request) {

  // wait until network is connected (max. 5 seconds)
  int connectionCheckCounter = 0;
  while (!ClientNetworkManager::_connectionSuccess && !ClientNetworkManager::_failedToConnect &&
         connectionCheckCounter < 200) {
    wxMilliSleep(25);
    connectionCheckCounter++;
  }

  // do not continue if failed to connect to server
  if (ClientNetworkManager::_failedToConnect) {
    return;
  }

  if (ClientNetworkManager::_connectionSuccess && ClientNetworkManager::_connection->is_connected()) {

    // serialize request into JSON string
    nlohmann::json json    = request;
    std::string    message = json.dump();

    // turn message into stream and prepend message length
    std::stringstream messageStream;
    messageStream << std::to_string(message.size()) << ':' << message;
    message = messageStream.str();

    // send message to server
    ssize_t bytesSent = ClientNetworkManager::_connection->write(message);

    // if the number of bytes sent does not match the length of the message, probably something went wrong
    if (bytesSent != ssize_t(message.length())) {
      GameController::showError(
          "Network error", "Error writing to the TCP stream: " + ClientNetworkManager::_connection->last_error_str(),
          false);
    }

  } else {
    GameController::showError("Network error", "Lost connection to server", true);
  }
}

std::unique_ptr<ServerResponse> ClientNetworkManager::parseResponse(const std::string &message) {
  LOG("About to parse response");
  LOG("Message: " + message);

  nlohmann::json json = nlohmann::json::parse(message);

  std::unique_ptr<ServerResponse> response = json;

  return response;
}
