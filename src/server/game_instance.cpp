//
// Created by Tejas Gupta on 4/19/23.
//

#include "game_instance.h"

#include "network/responses/ErrorResponse.h"
#include "network/responses/GameEvent.h"
#include "network/responses/JoinGameSuccess.h"
#include "network/responses/ServerResponse.h"
#include "server_network_manager.h"

bool game_instance::executeShot(CallShot shotRequest) {
  uuid    currPlayerID = shotRequest.getPlayerId();
  Player *currPlayer   = nullptr;
  Player *excluded     = nullptr;
  for (Player player : _game_state.get_players()) {
    if (player.getId() != currPlayerID) {
      excluded = &player;
    } else {
      currPlayer = &player;
    }
  }

  if (!_game_state.shotIsLegal(shotRequest.getPlayerId(), shotRequest.getPosition())) {
    // TODO: Send error message to player who attempted to make the shot
    //    std::string msg_string = "ERROR: ILLEGAL SHOT"; // TODO: figure out that JSON BITCH
    //    ServerResponse msg_string(ResponseType::ErrorResponse);
    BattleshipException exception("Error message");
    ErrorResponse      *error_response = new ErrorResponse(exception);
    ServerResponse     *msg_string     = error_response;
    server_network_manager::broadcast_message(*msg_string, _game_state.get_players(), excluded);
    return false;
  }

  // variables to be determined by game_state
  bool  hit;          // indicates if the shot was a hit
  Ship *hitShip;      // the ship that was hit (if there was a hit)
  bool  sunk;         // indicates if a ship was sunk
  uuid  nextPlayerId; // player who goes next

  // register shot and get results
  _game_state.registerShot(shotRequest.getPlayerId(), shotRequest.getPosition(), &hit, &hitShip, &sunk, &nextPlayerId);
  // TODO send gameEvent response to clients with this information
  GameEvent *shotCalled = new GameEvent(currPlayerID, shotRequest.getPosition(), hit, sunk, *hitShip, nextPlayerId);
  ServerResponse *msg_string = shotCalled;
  server_network_manager::broadcast_message(*msg_string, _game_state.get_players(), currPlayer);

  if (_game_state.gameOver()) {
    uuid winnerId = _game_state.getWinner();
    // TODO send GameOver response to clients
  }
}
bool game_instance::try_add_player(Player *new_player, std::string &err) {
  modification_lock.lock();
  if (_game_state.addPlayer(*new_player)) {
    // respond with JoinGameSuccess response
    JoinGameSuccess *msg_string = new JoinGameSuccess();
    server_network_manager::broadcast_message(*msg_string, _game_state.get_players(), new_player);
    modification_lock.unlock();
    return true;
  }
  modification_lock.unlock();
  return false;
}

// first boolean returns whether start_game was successful
// second boolean returns whether both players are ready to start the game
std::pair<std::pair<bool, bool>, std::vector<Player>> game_instance::start_game(Player *player, std::string &err) {
  modification_lock.lock();

  std::vector<Player> currentPlayers = _game_state.get_players();

  // indicates that the player is ready to the server
  if (_game_state.start(player->getId())) {
    std::cout << "In game_instance, game_State.start() returned true" << std::endl;

    modification_lock.unlock();
    bool oldAtLeastOnePlayerReady = atLeastOnePlayerReady;
    atLeastOnePlayerReady = true;

    std::cout << "Old value of atLeastOnePlayerReady: " << oldAtLeastOnePlayerReady << std::endl;

    std::pair<bool, bool> booleanPair = std::make_pair(true, oldAtLeastOnePlayerReady);
    return std::make_pair(booleanPair, currentPlayers);
  }
  modification_lock.unlock();

  std::pair<bool, bool> booleanPair = std::make_pair(false, false);
  return std::make_pair(booleanPair, currentPlayers);;
}

bool game_instance::joinGame(const JoinGame &joinGameRequest) {
  std::cout << "about to add player to the game state\n";
  std::lock_guard<std::mutex> lockGuard(modification_lock);

  uuid        playerId   = joinGameRequest.getPlayerId();
  std::string playerName = joinGameRequest.getPlayerName();
  Player      player     = Player(playerId, playerName);

//  // Prints out the names of the current players in the game
//  std::cout << "current players in the game:\n";
//  auto players = _game_state.get_players();
//  for (const auto& player : players) {
//    std::cout << "Player name: " << player.getName() << std::endl;
//  }

  return _game_state.addPlayer(player);
}
