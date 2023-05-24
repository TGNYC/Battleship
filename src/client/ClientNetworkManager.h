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
  static void init(const std::string &host, const uint16_t port);

  static void sendRequest(const ClientRequest &request);

  static std::unique_ptr<ServerResponse> parseResponse(const std::string &message);

private:
  static bool connect(const std::string &host, const uint16_t port);

  static sockpp::tcp_connector  *_connection;
  static ResponseListenerThread *_responseListenerThread;

  static bool _connectionSuccess;
  static bool _failedToConnect;
};

#endif // CLIENTNETWORKMANAGER_H