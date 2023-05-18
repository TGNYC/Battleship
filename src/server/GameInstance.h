//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_GAMEINSTANCE_H
#define BATTLESHIP_GAMEINSTANCE_H

#include "game_state/GameState.h"
#include "game_state/Player.h"
#include "network/requests/CallShot.h"
#include "network/requests/JoinGame.h"
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

class GameInstance {

private:
  GameState _game_state = GameState(GameState::Type::ServerState);
  // bool                     is_player_allowed_to_play(Player *player);
  inline static std::mutex       modification_lock;
  bool                           atLeastOnePlayerReady;
  std::unordered_map<uuid, bool> isReady;

public:
  GameInstance() {
    atLeastOnePlayerReady = false;
  }

  // unused functions
  // bool is_full();
  // bool is_started();
  // std::string get_id();
  // GameState *get_game_state();
  // bool is_finished();
  // bool try_add_player(Player *new_player, std::string &err);
  // bool draw_card(Player* player, card*& drawn_card, std::string& err);
  // bool play_card(Player* player, const std::string& card_id, std::string& err);
  // bool try_remove_player(Player *player, std::string &err);

  bool joinGame(const JoinGame &joinGameRequest);

  bool start_game(const Player *player, std::string &err);

  /*!
   * Function to handle a CallShot request. Registers the shot in the gameState. Sends out corresponding gameEvents.
   * Checks if the game is over.
   * @param shotRequest
   * @return
   */
  bool executeShot(CallShot shotRequest);

  GameState &getGameState();
  // TODO: play_again
};

#endif // BATTLESHIP_GAMEINSTANCE_H
