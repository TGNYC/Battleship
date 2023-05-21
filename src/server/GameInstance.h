//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_GAMEINSTANCE_H
#define BATTLESHIP_GAMEINSTANCE_H

#include "game_state/GameState.h"
#include "game_state/Player.h"
#include "network/requests/CallShot.h"
#include "network/requests/JoinGame.h"
#include "network/requests/QuitGame.h"
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

class GameInstance {

public:
  /*!
   * handles a client request to join the game. adds player to the GameState
   * @param joinGameRequest contains player name and id
   * @return true if player was added successfully, false otherwise
   */
  bool joinGame(const JoinGame &joinGameRequest);

  /*!
   * starts the game as soon as both players are ready
   * @param player the player who pressed ready
   * @param err
   * @return true if game was started. false if not started
   */
  bool startGame(const Player *player, std::string &err);


  bool executeShot(CallShot shotRequest);

  /*!
   * Function to handle a QuitGame request. Recreates a new GameState to be ready for next Game.
   * <>
   * @param QuitGame
   * @return True if all _gameState attributes are reset. Else, false.
   */
  bool quitGame(QuitGame quitGameRequest);
  // TODO: playAgain


  GameState &getGameState();

private:
  GameState                      _gameState = GameState(GameState::Type::ServerState);
  inline static std::mutex       _modification_lock;
  std::unordered_map<uuid, bool> _isReady; ///< keeps track which players pressed ready
};

#endif // BATTLESHIP_GAMEINSTANCE_H
