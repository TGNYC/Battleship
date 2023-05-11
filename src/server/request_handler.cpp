//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_REQUEST_HANDLER_CPP
#define BATTLESHIP_REQUEST_HANDLER_CPP

#include "request_handler.h"

#include "game_instance.h"
#include "network/requests/CallShot.h"
#include "network/requests/JoinGame.h"
#include "network/requests/PlayAgain.h"
#include "network/requests/SendEmote.h"
#include "network/requests/StartGame.h"
#include "network/responses/ErrorResponse.h"
#include "network/responses/JoinGameSuccess.h"
#include "network/responses/ServerResponse.h"
#include "player_manager.h"
#include <memory>

std::unique_ptr<ServerResponse> request_handler::handle_request(const ClientRequest *const req) {

  // Prepare variables that are used by every request type
  Player        *player;
  std::string    err;
  game_instance *game_instance_ptr = nullptr;

  // Get common properties of requests
  RequestType type = req->getRequestType();

  // Switch behavior according to request type
  switch (type) {

  // ##################### JOIN GAME #####################  //
  case RequestType::JoinGame: {
    const JoinGame joinGameRequest = static_cast<const JoinGame &>(*req);

    if (game_instance_ptr->joinGame(joinGameRequest)) {
      return std::make_unique<JoinGameSuccess>();
    } else {
      return std::make_unique<ErrorResponse>(BattleshipException("Faild to join the Game"));
    }
  } break;

  // TODO the other Requests
  default:
    return std::make_unique<ErrorResponse>(BattleshipException("Unkonwn Request"));
  }
}

#endif // LAMA_REQUEST_HANDLER_CPP
