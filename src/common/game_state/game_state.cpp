#include "game_state.h"
#include "Player.h"
#include <utility>
#include <stdexcept>

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
  m_playerGrids.emplace_back(playerId, std::move(shipPlacement));
  return true;
}

const PlayerGrid &game_state::getPlayerGrid(uuid playerId) const {
  for (auto grid : m_playerGrids) {
    if (grid.m_playerId == playerId) return grid;
  }
  throw std::runtime_error("Could not find grid for this player ID");
}

bool game_state::shotIsLegal(uuid playerId, Coordinate position) {
  if (position.x < 0 || position.x >= 10) return false;
  if (position.y < 0 || position.y >= 10) return false;
  const PlayerGrid& grid = getPlayerGrid(playerId);
  if (grid.shotsFired[position.x][position.y]) return false; // already fired at this tile
  return true;
}

bool game_state::updateBoards(GameEvent event) {
  uuid playerId = event.getPlayerId();
  Coordinate position = event.getPosition();

  if (m_playerGrids.size() == 2) { // we are on the server side

    auto shooter_grid = m_playerGrids[0]; // grid of the shooter
    auto target_grid  = m_playerGrids[1]; // grid of the victim/target
    if (shooter_grid.m_playerId == playerId) {
      std::swap(shooter_grid, target_grid);
    }

    int result = 1; // miss
    for (auto& ship : target_grid.m_shipsPlaced) {
      if (ship.hit(position)) {
        result = 2; // hit
      }
    }

    shooter_grid.shotsFired[position.x][position.y] = result;
    target_grid.shotsReceived[position.x][position.y] = result;


  } else if (m_playerGrids.size() == 1) { // client side
    auto my_grid = m_playerGrids[0];
    if (playerId == my_grid.m_playerId) {

    }
  }

  // loop through all ships and check for hit

}