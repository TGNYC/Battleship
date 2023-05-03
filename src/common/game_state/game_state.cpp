#include "game_state.h"
#include "Player.h"
#include <utility>

auto game_state::addPlayer(Player player) -> bool {
  // TODO check if player is alrady added
  if (m_players.size() >= 2) {
    return false;
  }
  m_players.push_back(std::move(player));
  return true;
}

auto game_state::addShips(uuid playerId, std::vector<Ship> shipPlacement) -> bool {
  // check for valid player id
  if(
      m_players.empty() ||
      (m_players.at(0).getId() != playerId && m_players.size() == 1) ||
      (m_players.at(0).getId() != playerId && m_players.at(1).getId() != playerId)
      ) {
    return false;
  }
  // TODO check if not alrady placed
  m_playerGrid.emplace_back(playerId, std::move(shipPlacement));
  return true;
}