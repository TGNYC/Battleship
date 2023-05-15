//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_PLAYER_MANAGER_H
#define BATTLESHIP_PLAYER_MANAGER_H

#include "game_state/Player.h"
#include <shared_mutex>
#include <string>
#include <unordered_map>

// TODO remove player manager since it seems obsolete
class player_manager {

private:
  inline static std::shared_mutex           _rw_lock;
  static std::unordered_map<uuid, Player *> _players_lut;

public:
  static bool try_get_player(uuid player_id, Player *&player_ptr);
  static bool add_or_get_player(std::string name, uuid player_id, Player *&player_ptr);
  static bool remove_player(uuid player_id, Player *&player); // not implemented
};

#endif // BATTLESHIP_PLAYER_MANAGER_H
