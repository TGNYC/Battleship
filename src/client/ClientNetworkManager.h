#ifndef CLIENTNETWORKMANAGER_H
#define CLIENTNETWORKMANAGER_H

#include "ResponseListenerThread.h"
#include "network/requests/ClientRequest.h"
#include "network/responses/ServerResponse.h"
#include "sockpp/tcp_connector.h"
#include <memory>
#include <string>

class ClientNetworkManager {
public:
  /*!
   * establishes a connection to the server specified by host address and port number
   * @param host server ip
   * @param port server port
   */
  static void init(const std::string &host, const uint16_t port);

  /*!
   * serializes and sends a client request to the server
   * @param request message to the server
   */
  static void sendRequest(const ClientRequest &request);

  /*!
   * deserializes a server response
   * @param message server response in json format
   * @return response object
   */
  static std::unique_ptr<ServerResponse> parseResponse(const std::string &message);

private:
  static bool connect(const std::string &host, const uint16_t port);

  static sockpp::tcp_connector  *_connection;
  static ResponseListenerThread *_responseListenerThread;

  static bool _connectionSuccess;
  static bool _failedToConnect;
};

#endif // CLIENTNETWORKMANAGER_H