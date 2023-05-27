//
// Created by Tejas Gupta on 4/19/23.
//

#include "GameInstance.h"
#include "Logger.h"
#include "ServerNetworkManager.h"
#include "network/responses/ErrorResponse.h"
#include "network/responses/GameEvent.h"
#include "network/responses/GameOverEvent.h"
#include "network/responses/JoinGameSuccess.h"
#include "network/responses/QuitGameEvent.h"
#include "network/responses/ServerResponse.h"
#include <cassert>

bool GameInstance::joinGame(const JoinGame &joinGameRequest) {
  LOG("about to add player to the game state");
  std::lock_guard<std::mutex> lockGuard(_modification_lock);

  uuid        playerId   = joinGameRequest.getPlayerId();
  std::string playerName = joinGameRequest.getPlayerName();
  Player      player     = Player(playerId, playerName);

  //  // Prints out the names of the current players in the game
  //  std::cout << "current players in the game:\n";
  //  auto players = _gameState.getPlayers();
  //  for (const auto& player : players) {
  //    std::cout << "Player name: " << player.getName() << std::endl;
  //  }

  return _gameState.addPlayer(player); // addPlayer checks if the player was already added or game is full
}

bool GameInstance::startGame(const Player &player, std::string &err) {

  LOG("GameInstance trying to start");
  std::lock_guard<std::mutex> lockGuard(_modification_lock);
  const std::vector<Player> currentPlayers = _gameState.getPlayers();

  // set this player to ready. not a problem if done more than once
  _isReady[player.getId()] = true;
  LOG(player.getId().ToString() + " is ready");

  // check if we have 2 players
  if (currentPlayers.size() != 2) {
    LOG("Not 2 players yet. Cannot start game. Number of players: " + std::to_string(currentPlayers.size()));
    return false;
  }

  // check if other player is ready
  const Player *otherPlayer = _gameState.getOtherPlayer(player.getId());
  assert(otherPlayer != nullptr);
  if (!_isReady[otherPlayer->getId()]) {
    LOG("Other player " + otherPlayer->getId().ToString() + " not ready yet. Cannot start game");
    return false;
  }

  // if reached here everything is fine and we can start
  LOG("Starting game state");
  return _gameState.start(player.getId()); // second player to press ready is first player to play
}

bool GameInstance::executeShot(CallShot shotRequest) {
  LOG("Executing shot...");
  // variables to be determined by GameState
  bool  hit;          // indicates if the shot was a hit
  Ship *hitShip;      // the ship that was hit (if there was a hit)
  bool  sunk;         // indicates if a ship was sunk
  uuid  nextPlayerId; // player who goes next

  // register shot and get results
  bool success = _gameState.registerShot(shotRequest.getPlayerId(), shotRequest.getPosition(), &hit, &hitShip, &sunk, &nextPlayerId);
  // build game event
  GameEvent *shotCalled = new GameEvent(shotRequest.getPlayerId(), shotRequest.getPosition(), hit, sunk, *hitShip, nextPlayerId);
  ServerResponse *msg_string = shotCalled;
  // broadcast to clients
  LOG("Sending GameEvent to clients");
  ServerNetworkManager::broadcastMessage(*msg_string, _gameState.getPlayers());

  LOG("checking for game over");
  if (_gameState.gameOver()) {
    LOG("game is over");
    uuid winnerId = _gameState.getWinner();
    LOG("winner is " + winnerId.ToString());
    GameOverEvent *gameOverEvent = new GameOverEvent(winnerId);
    ServerNetworkManager::broadcastMessage(*gameOverEvent, _gameState.getPlayers());
    LOG("broadcasted GameOverEvent to both clients");
    LOG("resetting GameInstance");
    reset();
  }
  return success;
}

bool GameInstance::reset() {
  // Set Mutex Lock
  std::lock_guard<std::mutex> lock(_modification_lock);
  _gameState.finish();
  LOG("removing both players from server");
  for (const Player &p : _gameState.getPlayers()) {
    ServerNetworkManager::onPlayerLeft(p.getId());
  }
  LOG("Recreating GameState in GameInstance. Ready for 2 new players to connect");
  _gameState = GameState(GameState::Type::ServerState); // Recreate GameState (which loses player information)
  _isReady.clear();
  return _gameState.getPlayers().empty(); // checks that _players attribute is an empty vec
}

GameState &GameInstance::getGameState() {
  return _gameState;
}