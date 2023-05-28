//
// Created by Tejas Gupta on 4/19/23.
//
#include "RequestHandler.h"

#include "GameInstance.h"
#include "Logger.h"
#include "ServerNetworkManager.h"
#include "network/requests/CallShot.h"
#include "network/requests/JoinGame.h"
#include "network/requests/QuitGame.h"
#include "network/requests/SendEmote.h"
#include "network/requests/StartGame.h"
#include "network/responses/ErrorResponse.h"
#include "network/responses/JoinGameSuccess.h"
#include "network/responses/QuitGameEvent.h"
#include "network/responses/ServerResponse.h"
#include "network/responses/StartGameSuccess.h"

std::unique_ptr<ServerResponse> RequestHandler::handleRequest(GameInstance              &gameInstance,
                                                              const ClientRequest *const req) {
  LOG("handling request");

  // Prepare variables that are used by every request type
  std::string err;

  // Get common properties of requests
  RequestType type     = req->getRequestType();
  uuid        playerId = req->getPlayerId();

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
    const Player   *player           = gameInstance.getGameState().getPlayer(playerId);
    LOG("adding ships of " + player->getName());
    gameInstance.getGameState().addShips(
        playerId, startGameRequest.getShips());
    // trying to start the gameInstance
    const bool result = gameInstance.startGame(*player, err); // this function does a lot of checks
    if (result) {
      LOG("request succeeded and both players are ready");
      std::unique_ptr<ServerResponse> resp =
          std::make_unique<StartGameSuccess>(gameInstance.getGameState().getPlayers(), playerId);
      ServerNetworkManager::broadcastMessage(*resp, gameInstance.getGameState().getPlayers(), nullptr);
      LOG("sent StartGameSuccess to both players");
      return nullptr;
    }
    LOG("Set player " + player->getName() + " ready. But opponent is not ready yet");
    return nullptr;
  } break;

  // ##################### CALL SHOT ##################### //
  case RequestType::CallShot: {
    LOG("Handle CallShot request");
    const CallShot callShotRequest = static_cast<const CallShot &>(*req);
    if (gameInstance.executeShot(callShotRequest)) { // if it worked
      return nullptr; // executeShot already broadcasts the gameEvent. no need for a personal response here
    } else {
      return std::make_unique<ErrorResponse>(BattleshipException("Failed to execute Shot"));
    }
  } break;

  // ##################### SEND EMOTE ##################### //
  case RequestType::SendEmote: {
    LOG("Handle SendEmote request");
    const Player                   *player           = gameInstance.getGameState().getPlayer(playerId);
    const SendEmote                 sendEmoteRequest = static_cast<const SendEmote &>(*req);
    std::unique_ptr<ServerResponse> response =
        std::make_unique<EmoteEvent>(sendEmoteRequest.getEmote(), sendEmoteRequest.getPlayerId());
    LOG("Sending EmoteEvent to the other player");
    ServerNetworkManager::broadcastMessage(*response, gameInstance.getGameState().getPlayers(), player);
    return nullptr; // nothing to send back to the request sender
  }

  // ##################### QUIT GAME ##################### //
  case RequestType::QuitGame: {
    LOG("handle Quit Game request");
    const QuitGame quitGameRequest = static_cast<const QuitGame &>(*req);
    const Player  *player          = gameInstance.getGameState().getPlayer(playerId);
    if (player == nullptr) { // if the player is not part of our game, no response needed. already removed him.
      return nullptr;
    }

    LOG("Player " + player->getName() + " quit the game.");

    if (gameInstance.getGameState().getState() == GameState::State::Starting && !gameInstance.isReady(*player)) {
      LOG("Player disconnected during setup phase. Just silently removing him");
      gameInstance.getGameState().removePlayer(*player);
      return nullptr;
    }

    LOG("sending QuitGameEvent to clients");
    std::unique_ptr<ServerResponse> response = std::make_unique<QuitGameEvent>(playerId);
    ServerNetworkManager::broadcastMessage(*response, gameInstance.getGameState().getPlayers(), player);

    LOG("resetting the gameInstance...");
    if (gameInstance.reset()) {
      LOG("gameInstance was reset");
      return nullptr;
    } else {
      LOG("problem while resetting the gameInstance");
      return nullptr;
    }
  }

  default: {
    LOG("Handle Unknown request");
    return std::make_unique<ErrorResponse>(BattleshipException("Unkonwn Request"));
  }
  }
}
