//
// Created by Tejas Gupta on 4/19/23.
//
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
#include "network/responses/StartGameSuccess.h"
#include "player_manager.h"
#include <iostream>
#include <memory>

std::unique_ptr<ServerResponse> request_handler::handle_request(game_instance             &gameInstance,
                                                                const ClientRequest *const req) {
  // Prepare variables that are used by every request type
  Player     *player;
  std::string err;

  // Get common properties of requests
  RequestType type      = req->getRequestType();
  uuid        player_id = req->getPlayerId();

  // Switch behavior according to request type
  switch (type) {
  case RequestType::JoinGame: {
    std::cout << "handle Join Game request\n";
    const JoinGame joinGameRequest = static_cast<const JoinGame &>(*req);

    if (gameInstance.joinGame(joinGameRequest)) {
      return std::make_unique<JoinGameSuccess>();
    } else {
      return std::make_unique<ErrorResponse>(BattleshipException("Faild to join the Game"));
    }
  } break;

  // ##################### START GAME ##################### //
  case RequestType::StartGame: {
    if (gameInstance.start_game(player, err)) {
      return std::make_unique<StartGameSuccess>(std::vector<Player>(), uuid()); // TODO return the correct values
    }
    return std::make_unique<ErrorResponse>(BattleshipException("Faild to start the Game"));
  } break;

  // ##################### CALL SHOT ##################### //
  // TODO: finish implementing the call shot request
  case RequestType::CallShot: {
    if (gameInstance.executeShot((*(CallShot *)req))) { // if it worked
      return std::make_unique<GameEvent>(player_id, Coordinate(), false, false,
                                         Ship(0, Coordinate(), Ship::Orientation::Horizontal, uuid()), uuid());
    } else {
      return std::make_unique<ErrorResponse>(BattleshipException("Faild to execute Shot"));
    }
  } break;

  // ##################### SEND EMOTE ##################### //
  // TODO: finish send_emote request handler
  //    case RequestType::send_emote: {}

  // ##################### QUIT GAME ##################### //
  // TODO: finish quit_game request handler
  //    case RequestType::quit_game: { }

  // TODO the other Requests
  default: {
    std::cout << "handle Unkonwn request\n";
    return std::make_unique<ErrorResponse>(BattleshipException("Unkonwn Request"));
  }
  }
}
