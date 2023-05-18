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
  static std::unique_ptr<ServerResponse> handle_request(GameInstance &gameInstance, const ClientRequest *const req);
};

#endif // BATTLESHIP_REQUESTHANDLER_H
