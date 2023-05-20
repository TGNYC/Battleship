//
// Created by Tejas Gupta on 4/19/23.
//

#include "Player.h"

#include <utility>

Player::Player(uuid playerId, std::string player_name) : _id(playerId), _name(std::move(player_name)) {}

auto Player::getId() const -> uuid {
  return _id;
}

auto Player::getName() const -> std::string {
  return _name;
}
