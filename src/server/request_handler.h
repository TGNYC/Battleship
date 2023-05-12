//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_REQUEST_HANDLER_H
#define BATTLESHIP_REQUEST_HANDLER_H

#include "game_instance.h"
#include "network/requests/ClientRequest.h"
#include "network/responses/ServerResponse.h"
#include <memory>

class request_handler {
public:
  static std::unique_ptr<ServerResponse> handle_request(const ClientRequest *const req);

  static game_instance *current_game;
};

#endif // BATTLESHIP_REQUEST_HANDLER_H
