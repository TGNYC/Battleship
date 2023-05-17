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
#include "server_network_manager.h"
#include <iostream>
#include <memory>

std::unique_ptr<ServerResponse> request_handler::handle_request(game_instance             &gameInstance,
                                                                const ClientRequest *const req) {
  std::cout << "handle_request() called\n";

  // Prepare variables that are used by every request type
  // Player     *player; //TODO remove this line. dangerous to deal with uninitialized player due to random uuid
  std::string err;

  // Get common properties of requests
  RequestType type      = req->getRequestType();
  uuid        player_id = req->getPlayerId();
  // const Player* player = &gameInstance.getGameState().getPlayer(player_id);

  // Switch behavior according to request type
  switch (type) {

    // ##################### JOIN GAME ##################### //
  case RequestType::JoinGame: {
    std::cout << "handle Join Game request\n";
    const JoinGame joinGameRequest = static_cast<const JoinGame &>(*req);

    if (gameInstance.joinGame(joinGameRequest)) {
      return std::make_unique<JoinGameSuccess>();
    } else {
      return std::make_unique<ErrorResponse>(BattleshipException("Failed to join the Game"));
    }
  } break;

  // ##################### START GAME ##################### //
  case RequestType::StartGame: {
    std::cout << "handle Start Game request\n";
    const Player player = gameInstance.getGameState().getPlayer(player_id);
    bool         result = gameInstance.start_game(&player, err);
    std::cout << "start game result " << result << std::endl;
    // indicates that both players are ready to the server by sending a success response to the current player's server
    // (the response to the other player is sent in the logic in game_instance)
    if (result) {
      std::cout << "Request succeeded and both players are ready" << std::endl;

      // send StartGameSuccess update to the already-ready player
      std::cout << "Sending StartGameSuccess to the already-ready player" << std::endl;
      std::unique_ptr<ServerResponse> resp =
          std::make_unique<StartGameSuccess>(gameInstance.getGameState().get_players(), player_id);
      server_network_manager::broadcast_message(*resp, gameInstance.getGameState().get_players(), &player);

      // send StartGameSuccess update to the newly-ready player
      std::cout << "Sending StartGameSuccess to the newly-ready player" << std::endl;
      return std::make_unique<StartGameSuccess>(gameInstance.getGameState().get_players(),
                                                player_id); // TODO can you pass here the resp pointer from above?
    }
    std::cout << "Request succeeded and set player ready. But opponent not ready yet" << std::endl;
    return nullptr;
  } break;

  // ##################### CALL SHOT ##################### //
  // TODO: finish implementing the call shot request
  case RequestType::CallShot: {
    if (gameInstance.executeShot((*(CallShot *)req))) { // if it worked
      // TODO : currently the GameEvent is only sent to the player who called the shot. Change to make it go to both
      return std::make_unique<GameEvent>(player_id, Coordinate(), false, false,
                                         Ship(0, Coordinate(), Ship::Orientation::Horizontal, uuid()), uuid());
    } else {
      return std::make_unique<ErrorResponse>(BattleshipException("Failed to execute Shot"));
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
