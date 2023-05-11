//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_REQUEST_HANDLER_CPP
#define BATTLESHIP_REQUEST_HANDLER_CPP

#include "request_handler.h"

#include "game_instance.h"
<<<<<<< HEAD
#include "player_manager.h"
#include "../common/network/responses/ServerResponse.h"

// TODO: link other files in server
// #include "player_manager.h"
 #include "game_instance_manager.h"
 #include "game_instance.h"
//
// #include "../common/network/requests/join_game_request.h"
// #include "../common/network/requests/draw_card_request.h"
// #include "../common/network/requests/play_card_request.h"

=======
>>>>>>> 40180b2488690ca1c9af3c21cb848a3dfcaa196f
#include "network/requests/CallShot.h"
#include "network/requests/JoinGame.h"
#include "network/requests/PlayAgain.h"
#include "network/requests/SendEmote.h"
#include "network/requests/StartGame.h"
<<<<<<< HEAD
#include "network/responses/RequestResponse.h"
=======
#include "network/responses/ErrorResponse.h"
#include "network/responses/JoinGameSuccess.h"
>>>>>>> 40180b2488690ca1c9af3c21cb848a3dfcaa196f
#include "network/responses/ServerResponse.h"
#include "player_manager.h"
#include <memory>

<<<<<<< HEAD
static game_instance* current_game = nullptr;

ServerResponse *request_handler::handle_request(const ClientRequest *const req) {
    // Prepare variables that are used by every request type
    Player        *player;
    std::string    err;
    game_instance *game_instance_ptr = nullptr;

    // Get common properties of requests
    RequestType type      = req->getRequestType();
    uuid player_id        = req->getPlayerId(); // check if uuid imported
//    RequestType type      = req->get_type();
//    std::string req_id    = req->get_req_id();
    std::string        game_id   = "0"; //req->get_game_id(); // maybe unnecessary since only 1 game
//    std::string player_id = req->get_player_id();
=======
std::unique_ptr<ServerResponse> request_handler::handle_request(const ClientRequest *const req) {

  // Prepare variables that are used by every request type
  Player        *player;
  std::string    err;
  game_instance *game_instance_ptr = nullptr;
>>>>>>> 40180b2488690ca1c9af3c21cb848a3dfcaa196f

  // Get common properties of requests
  RequestType type = req->getRequestType();

<<<<<<< HEAD
    // ##################### JOIN GAME #####################  //
    case RequestType::JoinGame: {
      std::string player_name = ((JoinGame *)req)->getPlayerName();

      // check if game is created, if not create it
      if (current_game == nullptr) {
        current_game = new game_instance();
      }

      // try to add player to the game
      if (current_game->try_add_player(player, err)) {
          return new RequestResponse(player_id, true, type);
      } else { // if adding player failed
          return new RequestResponse(player_id, false, type);
      }
=======
  // Switch behavior according to request type
  switch (type) {

  // ##################### JOIN GAME #####################  //
  case RequestType::JoinGame: {
    const JoinGame joinGameRequest = static_cast<const JoinGame &>(*req);

    if (game_instance_ptr->joinGame(joinGameRequest)) {
      return std::make_unique<JoinGameSuccess>();
    } else {
      return std::make_unique<ErrorResponse>(BattleshipException("Faild to join the Game"));
>>>>>>> 40180b2488690ca1c9af3c21cb848a3dfcaa196f
    }
  } break;

<<<<<<< HEAD
    // ##################### START GAME ##################### //
    case RequestType::StartGame: {
      if (current_game->start_game(player, err)) {
        return new RequestResponse(player_id, true, type);
      }
      return new RequestResponse(player_id, false, type);
    }

    // ##################### CALL SHOT ##################### //
    // TODO: finish implementing the call shot request
    case RequestType::CallShot: {
      if (current_game->executeShot((*(CallShot *)req))) { // if it worked
          RequestResponse* response = new RequestResponse(player_id, true, type);
          return response;
      } else {
          return new RequestResponse(player_id, false, type);
      }
    }

    // ##################### SEND EMOTE ##################### //
    // TODO: finish send_emote request handler
//    case RequestType::send_emote: {}

    // ##################### QUIT GAME ##################### //
    // TODO: finish quit_game request handler
//    case RequestType::quit_game: { }

    // ##################### UNKNOWN REQUEST ##################### //
    default:
      return new request_response("", req_id, false, nullptr, "Unknown RequestType " + type);
    }
=======
  // TODO the other Requests
  default:
    return std::make_unique<ErrorResponse>(BattleshipException("Unkonwn Request"));
  }
>>>>>>> 40180b2488690ca1c9af3c21cb848a3dfcaa196f
}

#endif // LAMA_REQUEST_HANDLER_CPP
