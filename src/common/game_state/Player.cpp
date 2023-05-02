//
// Created by Tejas Gupta on 4/19/23.
//

#include "Player.h"

Player::Player(uuid playerId, std::string player_name) : m_name(player_name), m_id(playerId) {}

auto Player::getId() const -> uuid {
  return m_id;
}
