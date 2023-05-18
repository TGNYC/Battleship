//
// Created by Tejas Gupta on 4/19/23.
//
#include "RequestHandler.h"

#include "GameInstance.h"
#include "Logger.h"
#include "ServerNetworkManager.h"
#include "network/requests/CallShot.h"
#include "network/requests/JoinGame.h"
#include "network/requests/PlayAgain.h"
#include "network/requests/SendEmote.h"
#include "network/requests/StartGame.h"
#include "network/responses/ErrorResponse.h"
#include "network/responses/JoinGameSuccess.h"
#include "network/responses/ServerResponse.h"
#include "network/responses/StartGameSuccess.h"
#include <iostream>
#include <memory>

std::unique_ptr<ServerResponse> RequestHandler::handle_request(GameInstance              &gameInstance,
                                                                const ClientRequest *const req) {
  LOG("handling request");

  // Prepare variables that are used by every request type
  std::string err;

  // Get common properties of requests
  RequestType type      = req->getRequestType();
  uuid        player_id = req->getPlayerId();

  // Switch behavior according to request type
  switch (type) {

    // ##################### JOIN GAME ##################### //
  case RequestType::JoinGame: {
    LOG("handle Join Game request");
    const JoinGame joinGameRequest = static_cast<const JoinGame &>(*req);

    if (gameInstance.joinGame(joinGameRequest)) {
      return std::make_unique<JoinGameSuccess>();
    } else {
      return std::make_unique<ErrorResponse>(BattleshipException("Failed to join the Game"));
    }
  } break;

  // ##################### START GAME ##################### //
  case RequestType::StartGame: {
    LOG("handle StartGame request");
    const StartGame startGameRequest = static_cast<const StartGame &>(*req);
    const Player player = gameInstance.getGameState().getPlayer(player_id);
    LOG("adding ships of " + player.getName());
    gameInstance.getGameState().addShips(player_id, startGameRequest.getShips()); // TODO move this line to gameInstance.startGame()
    // trying to start the gameInstance
    const bool result = gameInstance.startGame(&player, err);  // this function does a lot of checks

    // indicates that both players are ready to the server by sending a success response to the current player's server
    // (the response to the other player is sent in the logic in game_instance)
    if (result) {
      LOG("Request succeeded and both players are ready");
      // send StartGameSuccess update to the already-ready player
      LOG("Sending StartGameSuccess to the already-ready player");
      std::unique_ptr<ServerResponse> resp =
          std::make_unique<StartGameSuccess>(gameInstance.getGameState().getPlayers(), player_id);
      ServerNetworkManager::broadcast_message(*resp, gameInstance.getGameState().getPlayers(), &player);
      // send StartGameSuccess update to the newly-ready player
      LOG("Sending StartGameSuccess to the newly-ready player");
      return std::make_unique<StartGameSuccess>(gameInstance.getGameState().getPlayers(),
                                                player_id); // TODO can you pass here the resp pointer from above?
    }
    LOG("Set player " + player.getName() + " ready. But opponent is not ready yet");
    return nullptr;
  } break;

  // ##################### CALL SHOT ##################### //
  case RequestType::CallShot: {
    LOG("Handle CallShot request");
    const CallShot callShotRequest = static_cast<const CallShot&>(*req);
    if (gameInstance.executeShot(callShotRequest)) { // if it worked
      return nullptr; // executeShot already broadcasts the gameEvent. no need for a personal response here
    } else {
      return std::make_unique<ErrorResponse>(BattleshipException("Failed to execute Shot"));
    }
  } break;

  // ##################### SEND EMOTE ##################### //
  case RequestType::SendEmote: {
    LOG("Handle SendEmote request");
    const Player player = gameInstance.getGameState().getPlayer(player_id);
    const SendEmote sendEmoteRequest = static_cast<const SendEmote&>(*req);
    std::unique_ptr<ServerResponse> response = std::make_unique<EmoteEvent>(sendEmoteRequest.getEmote(),
                                                                            sendEmoteRequest.getPlayerId());
    LOG("Sending EmoteEvent to the other player");
    ServerNetworkManager::broadcast_message(*response, gameInstance.getGameState().getPlayers(), &player);
    return nullptr; // nothing to send back to the request sender
  }

  // ##################### QUIT GAME ##################### //
  // TODO: finish quit_game request handler
  //    case RequestType::quit_game: { }

    // TODO PlayAgain
    // TODO QuitGame
  default: {
    LOG("Handle Unkonwn request");
    return std::make_unique<ErrorResponse>(BattleshipException("Unkonwn Request"));
  }
  }
}
