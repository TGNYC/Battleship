//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_REQUEST_HANDLER_CPP
#define BATTLESHIP_REQUEST_HANDLER_CPP

#include "request_handler.h"
#include "game_instance.h"
#include "player_manager.h"

// TODO for common: create join_game_request (JoinGame, StartGame, QuitGame, PlayAgain)
// TODO for common: create call_shot_request (CallShot)
// TODO for common: create send_emote_request (SendEmote)

// TODO: link other files in server
// #include "player_manager.h"
// #include "game_instance_manager.h"
// #include "game_instance.h"
//
// #include "../common/network/requests/join_game_request.h"
// #include "../common/network/requests/draw_card_request.h"
// #include "../common/network/requests/play_card_request.h"

#include "network/requests/JoinGame.h"
#include "network/requests/StartGame.h"
#include "network/requests/CallShot.h"
#include "network/requests/SendEmote.h"
#include "network/requests/PlayAgain.h"


request_response *request_handler::handle_request(const ClientRequest *const req) {
  /*
    // Prepare variables that are used by every request type
    Player        *player;
    std::string    err;
    game_instance *game_instance_ptr = nullptr;

    // Get common properties of requests
    RequestType type      = req->get_type();
    std::string req_id    = req->get_req_id();
    uuid        game_id   = req->get_game_id(); // maybe unnecessary since only 1 game
    std::string player_id = req->get_player_id();

    // Switch behavior according to request type
    switch (type) {

    // ##################### JOIN GAME #####################  //
    case RequestType::JoinGame: {
      std::string player_name = ((join_game_request *)req)->get_player_name();

      // Create new player or get existing one with that name
      player_manager::add_or_get_player(player_name, player_id, player);

      if (game_id.empty()) {
        // join any game
        if (game_instance_manager::try_add_player_to_any_game(player, game_instance_ptr, err)) {
          // game_instance_ptr got updated to the joined game

          // return response with full game_state attached
          return new request_response(game_instance_ptr->get_id(), req_id, true,
                                      game_instance_ptr->get_game_state()->to_json(), err);
        } else {
          // failed to find game to join
          return new request_response("", req_id, false, nullptr, err);
        }
      } else {
        // join a specific game denoted by req->get_game_id()
        if (game_instance_manager::try_get_game_instance(game_id, game_instance_ptr)) {
          if (game_instance_manager::try_add_player(player, game_instance_ptr, err)) {
            // return response with full game_state attached
            return new request_response(game_id, req_id, true, game_instance_ptr->get_game_state()->to_json(), err);
          } else {
            // failed to join requested game
            return new request_response("", req_id, false, nullptr, err);
          }
        } else {
          // failed to find requested game
          return new request_response("", req_id, false, nullptr, "Requested game could not be found.");
        }
      }
    }

    // ##################### START GAME ##################### //
    case RequestType::start_game: {
      if (game_instance_manager::try_get_player_and_game_instance(player_id, player, game_instance_ptr, err)) {
        if (game_instance_ptr->start_game(player, err)) {
          return new request_response(game_instance_ptr->get_id(), req_id, true,
                                      game_instance_ptr->get_game_state()->to_json(), err);
        }
      }
      return new request_response("", req_id, false, nullptr, err);
    }

    // ##################### CALL SHOT ##################### //
    // TODO: finish implementing the call shot request
    case RequestType::call_shot: {
      if (game_instance_manager::try_get_player_and_game_instance(player_id, player, game_instance_ptr, err)) {
        //      card *drawn_card;
        //      std::string card_id = ((play_card_request *) req)->get_card_id();
        //      if (game_instance_ptr->play_card(player, card_id, err)) {
        //        return new request_response(game_instance_ptr->get_id(), req_id, true,
        //                                    game_instance_ptr->get_game_state()->to_json(), err);
        //      }
        //    }
        return new request_response("", req_id, false, nullptr, err);
      }
    }

    // ##################### SEND EMOTE ##################### //
    // TODO: finish send_emote request handler
    case RequestType::send_emote: {
      if (game_instance_manager::try_get_player_and_game_instance(player_id, player, game_instance_ptr, err)) {
        //      card *drawn_card;
        //      // int nof_cards = ((draw_card_request*)req)->get_nof_cards();
        //      if (game_instance_ptr->draw_card(player, drawn_card, err)) {
        //        return new request_response(game_instance_ptr->get_id(), req_id, true,
        //                                    game_instance_ptr->get_game_state()->to_json(), err);
        //      }
        //    }
        return new request_response("", req_id, false, nullptr, err);
      }
    }

    // ##################### QUIT GAME ##################### //
    // TODO: finish quit_game request handler
    case RequestType::quit_game: {
      if (game_instance_manager::try_get_player_and_game_instance(player_id, player, game_instance_ptr, err)) {
        //    if (game_instance_ptr->start_game(player, err)) {
        //        return new request_response(game_instance_ptr->get_id(), req_id, true,
        //                                    game_instance_ptr->get_game_state()->to_json(), err);
        //    }
      }
      return new request_response("", req_id, false, nullptr, err);
    }

    // ##################### UNKNOWN REQUEST ##################### //
    default:
      return new request_response("", req_id, false, nullptr, "Unknown RequestType " + type);
    }
    */
}

#endif // LAMA_REQUEST_HANDLER_CPP
