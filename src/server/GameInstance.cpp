//
// Created by Tejas Gupta on 4/19/23.
//

#include "GameInstance.h"
#include "Logger.h"
#include "ServerNetworkManager.h"
#include "network/responses/ErrorResponse.h"
#include "network/responses/GameEvent.h"
#include "network/responses/QuitGameEvent.h"
#include "network/responses/JoinGameSuccess.h"
#include "network/responses/ServerResponse.h"

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

// is called upon receiving a startGameRequest
// first boolean returns whether start_game was successful
// second boolean returns whether both players are ready to start the game
bool GameInstance::startGame(const Player *player, std::string &err) {

  LOG("GameInstance trying to start");
  std::lock_guard<std::mutex> lockGuard(_modification_lock);
  const std::vector<Player> currentPlayers = _gameState.getPlayers();

  // set this player to ready. not a problem if done more than once
  _isReady[player->getId()] = true;
  LOG(player->getId().ToString() + " is ready");

  // check if we have 2 players
  if (currentPlayers.size() != 2) {
    LOG("Not 2 players yet. Cannot start game");
    return false;
  }

  // check if other player is ready
  const Player &otherPlayer = _gameState.getOtherPlayer(player->getId());
  if (!_isReady[otherPlayer.getId()]) {
    LOG("Other player " + otherPlayer.getId().ToString() + " not ready yet. Cannot start game");
    return false;
  }

  // if reached here everything is fine and we can start
  LOG("Starting game state");
  return _gameState.start(player->getId()); // second player to press ready is first player to play for the moment
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
  if (_gameState.gameOver()) {
    uuid winnerId = _gameState.getWinner();
    // TODO send GameOver response to clients
  }
  return success;
}

bool GameInstance::quitGame(QuitGame quitGameRequest) {
  // Set Mutex Lock
  std::lock_guard<std::mutex> lock(_modification_lock);
  // Broadcast to all users QuitGameEvent
  QuitGameEvent *gameQuit = new QuitGameEvent(quitGameRequest.getPlayerId());
  ServerResponse *msg_string = gameQuit;
  LOG("Sending QuitGameEvent to clients");
  ServerNetworkManager::broadcastMessage(*msg_string, _gameState.getPlayers());

  // Recreate GameState (which loses player information)
  LOG("Recreating GameState in a GameInstance");
  _gameState = GameState(GameState::Type::ServerState);
  _gameState.setStateFinished();
  _isReady.clear();
  return _gameState.getPlayers().empty(); // checks that _players attribute is an empty vec
}

GameState &GameInstance::getGameState() {
  return _gameState;
}

// TODO remove because never used. functionality is implemented in game_instance::joinGame
/*bool game_instance::try_add_player(Player *new_player, std::string &err) {
  _modification_lock.lock();
  if (_gameState.addPlayer(*new_player)) {
    // respond with JoinGameSuccess response
    JoinGameSuccess *msg_string = new JoinGameSuccess();
    server_network_manager::broadcast_message(*msg_string, _gameState.getPlayers(), new_player);
    _modification_lock.unlock();
    return true;
  }
  _modification_lock.unlock();
  return false;
}*/
