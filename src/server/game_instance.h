//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_GAME_INSTANCE_H
#define BATTLESHIP_GAME_INSTANCE_H

#include <mutex>
#include <string>
#include <vector>

#include "game_state/Player.h"
#include "game_state/game_state.h"
#include "network/requests/CallShot.h"
#include "network/requests/JoinGame.h"

class game_instance {

private:
  game_state              *_game_state;
  bool                     is_player_allowed_to_play(Player *player);
  inline static std::mutex modification_lock;

public:
  game_instance();
  ~game_instance() {
    if (_game_state != nullptr) {
      delete _game_state;
    }
    _game_state = nullptr;
  }
  std::string get_id();

  game_state *get_game_state();

  bool is_full();
  bool is_started();
  bool is_finished();

  // game update functions
  bool start_game(Player *player, std::string &err);
  bool try_add_player(Player *new_player, std::string &err);
  bool try_remove_player(Player *player, std::string &err);
  /*!
   * Function to handle a CallShot request. Registers the shot in the gameState. Sends out corresponding gameEvents.
   * Checks if the game is over.
   * @param shotRequest
   * @return
   */

  bool executeShot(CallShot shotRequest);
  // TODO: play_again

  //  bool draw_card(Player* player, card*& drawn_card, std::string& err);
  //  bool play_card(Player* player, const std::string& card_id, std::string& err);
  //  bool fold(player* Player, std::string& err);

  bool joinGame(JoinGame joinGameRequest);
};

#endif // BATTLESHIP_GAME_INSTANCE_H
