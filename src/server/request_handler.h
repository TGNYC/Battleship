//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_REQUEST_HANDLER_H
#define BATTLESHIP_REQUEST_HANDLER_H

#include "network/requests/ClientRequest.h"
#include "network/responses/ServerResponse.h"
#include "game_instance.h"

class request_handler {
public:
  static ServerResponse *handle_request(const ClientRequest *const req);
  static game_instance* current_game;
};

#endif // BATTLESHIP_REQUEST_HANDLER_H
