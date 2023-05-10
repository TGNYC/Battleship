//
// Created by Tejas Gupta on 4/19/23.
//

#include "Player.h"

#include <utility>

Player::Player(uuid playerId, std::string player_name) : m_id(playerId), m_name(std::move(player_name)) {}

auto Player::getId() const -> uuid {
  return m_id;
}

auto Player::getName() const -> std::string {
  return m_name;
}
