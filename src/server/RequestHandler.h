//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_REQUESTHANDLER_H
#define BATTLESHIP_REQUESTHANDLER_H

#include "GameInstance.h"
#include "network/requests/ClientRequest.h"
#include "network/responses/ServerResponse.h"
#include <memory>

class RequestHandler {
public:
  /*!
   * Handles an incoming request from the ServerNetworkManager and generates a response.
   * @param gameInstance
   * @param req
   * @return direct response to send back (only) to the sender of the request
   */
  static std::unique_ptr<ServerResponse> handleRequest(GameInstance &gameInstance, const ClientRequest *const req);
};

#endif // BATTLESHIP_REQUESTHANDLER_H
