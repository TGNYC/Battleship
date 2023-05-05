#include "game_state.h"
#include "Player.h"
#include <utility>
#include <stdexcept>
#include <cassert>
#include "Logger.h"


auto game_state::addPlayer(Player player) -> bool {
  // check if player is alrady added
  for (const Player& p : m_players) {
    if (p.getId() == player.getId()) {
      return false;
    }
  }
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

  // check if not already placed
  for (const PlayerGrid& grid : m_playerGrids) {
    if (grid.m_playerId == playerId) {
      Logger::log("Ship placement for this player id already exists", Logger::Type::warning);
      return false;
    }
  }
  m_playerGrids.emplace_back(playerId, std::move(shipPlacement));
  return true;
}


PlayerGrid &game_state::getPlayerGrid(uuid playerId) {
  for (PlayerGrid& grid : m_playerGrids) {
    if (grid.m_playerId == playerId) return grid;
  }
  throw std::runtime_error("Could not find grid for this player ID");
}

Ship &game_state::getShip(std::vector<Ship>& ships, uuid shipId) {
  for (Ship& ship : ships) {
    if (ship.getId() == shipId) {
      return ship;
    }
  }
  Logger::log("GameState::getShip: no ship with matching id found", Logger::Type::error);
}

uuid game_state::getOtherPlayer(uuid playerId) {
  for (const Player& player : m_players) {
    if (player.getId() != playerId) {
      return player.getId();
    }
  }
  Logger::log("Fatal Error: did not find other player", Logger::Type::error);
  return uuid("Error");
}

bool game_state::shotIsLegal(uuid playerId, Coordinate position) {
  if (position.x < 0 || position.x >= 10) return false;
  if (position.y < 0 || position.y >= 10) return false;
  const PlayerGrid& grid = getPlayerGrid(playerId);
  if (grid.shotsFired[position.x][position.y]) return false; // already fired at this tile
  return true;
}

// all parameters after position are used to return info back to the caller
bool game_state::registerShot(uuid playerId, Coordinate position, bool *hit, Ship **hitShipPtr, bool *sunk, uuid *nextPlayerId) {

  // log turn number
  Logger::log("Turn Number {}. Player {} is playing",Logger::Type::info);

  // make sure we are on a server
  assert(m_playerGrids.size() == 2 && "Number of grids is not 2. Illegal call on client side or incomplete state on server");

  // check if the correct player is playing
  if (playerId != currentPlayerId) {
    Logger::log("GameState::registerShot: It is not this players turn", Logger::Type::error);
    return false;
  }

  // get the player grids
  PlayerGrid shooterGrid  = m_playerGrids[0]; // grid of the shooter
  PlayerGrid targetGrid   = m_playerGrids[1]; // grid of the victim/target
  if (shooterGrid.m_playerId == playerId) {
    std::swap(shooterGrid, targetGrid);
  }
  const uuid targetPlayerId = targetGrid.m_playerId;

  // set default values
  *hit = false;
  *sunk = false;
  *hitShipPtr = nullptr;

  // loop through all ships
  for (Ship& ship : targetGrid.m_shipsPlaced) {
    if (ship.hit(position)) {
      *hit = true;
      *hitShipPtr = &ship;
      if (ship.hasSunken()) {
        *sunk = true;
      }
      break; // if a ship was hit, we can stop the loop
    }
  }

  // update server side game state
  const int impact = *hit ? 2 : 1;  // 2=hit 1=miss
  shooterGrid.shotsFired[position.x][position.y] = impact;
  targetGrid.shotsReceived[position.x][position.y] = impact;

  // determine next player
  *nextPlayerId = *hit ? playerId : targetPlayerId; // if shot was a hit, the current player goes again. otherwise switch
  currentPlayerId = *nextPlayerId;  // update current player
  turnNumber++;
  return true;
}

bool game_state::updateBoards(GameEvent &event) {

  // make sure we are on a client
  assert(m_playerGrids.size() == 1 && "Number of grids is not 1. Illegal call on server side or damaged state on client");

  PlayerGrid myGrid = m_playerGrids[0];

  // update my grid
  if (event.playerId == myGrid.m_playerId) {  // I called the shot
      myGrid.shotsFired[event.position.x][event.position.y] = event.hit ? 2 : 1;
  } else { // other player shot me
      // update shots
      myGrid.shotsReceived[event.position.x][event.position.y] = event.hit ? 2 : 1;
      // update my ships
      Ship& hitShip = getShip(myGrid.m_shipsPlaced, event.hitShip.getId()); // find out which of my local ships was hit
      hitShip.hit(event.position);
  }

  // update current player
  currentPlayerId = event.nextPlayerId;
}

bool game_state::gameOver(uuid *winner) {
  *winner = uuid("diniMueter");

  assert(m_playerGrids.size() == 2 && "Number of grids is not 2. Cannot determine round win.");

  for (const PlayerGrid& grid: m_playerGrids) {
      bool lost = true;
      for (const Ship& ship : grid.m_shipsPlaced) {
        if (!ship.hasSunken()) {  // at least one ship still alive, therefore not lost yet
          lost = false;
          break;
        }
      }
      if (lost) {
        *winner = getOtherPlayer(grid.m_playerId); // this player lost, so the other player is the winner
        isFinished = true;
        m_state = State::Finished;
        return true;
      }
  }
  return false;
}