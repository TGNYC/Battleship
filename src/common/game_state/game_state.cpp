#include "game_state.h"
#include "Player.h"
#include <utility>
#include <stdexcept>
#include <cassert>
#include "Logger.h"


game_state::game_state(game_state::Type type) :
      state(State::Starting),
      type(type),
      currentPlayerId(),
      turnNumber(0) {

  players = std::vector<Player>();
  playerGrids = std::vector<PlayerGrid>();
  LOG("Created GameState");
}


auto game_state::addPlayer(Player player) -> bool {
  // check if player is already added
  for (const Player& p : players) {
    if (p.getId() == player.getId()) {
      return false;
    }
  }
  if (players.size() >= 2) {
    return false;
  }
  LOG("Added Player to GameState: " + player.getName() + " " + player.getId().ToString());
  players.push_back(std::move(player));
  return true;
}


auto game_state::addShips(uuid playerId, std::vector<Ship> shipPlacement) -> bool {
  // check for valid player id
  if(players.empty() ||
      (players.at(0).getId() != playerId && players.size() == 1) ||
      (players.at(0).getId() != playerId && players.at(1).getId() != playerId)
      ) {
    return false;
  }
  // check if not already placed
  for (const PlayerGrid& grid : playerGrids) {
    if (grid.playerId == playerId) {
      LOG("Ship placement for this player id already exists");
      return false;
    }
  }
  // create playerGrid and add it to the vector
  LOG("Added Ships of " + playerId.ToString() + " to GameState");
  playerGrids.emplace_back(playerId, std::move(shipPlacement));
  return true;
}


bool game_state::start(uuid currentPlayerId) {
  if (state != State::Starting) {
    LOG("Game state not in starting phase. Cannot start game.");
    return false;
  } else if (players.size() != 2) {
    LOG("Number of players is not 2. Cannot start game.");
    return false;
  } else if (type == Type::ServerState && playerGrids.size() != 2) {
    LOG("Not 2 grids on server. Cannot start game.");
    return false;
  } else if (type == Type::ClientState && playerGrids.size() != 1) {
    LOG("Not 1 grid on client. Cannot start game.");
    return false;
  } else {
    this->currentPlayerId = currentPlayerId;
    LOG("first to play: " + currentPlayerId.ToString());
    state = State::Playing;
    LOG("Successfully started GameState");
    return true;
  }
}


uuid game_state::getCurrentPlayerId() {
  return currentPlayerId;
}


const PlayerGrid &game_state::getPlayerGrid(uuid playerId) const {
  for (const PlayerGrid& grid : playerGrids) {
    if (grid.playerId == playerId) {
      return grid;
    }
  }
  throw std::runtime_error("Could not find grid for this player id");
}


Ship &game_state::getShip(std::vector<Ship>& ships, uuid shipId) {
  for (Ship& ship : ships) {
    if (ship.getId() == shipId) {
      return ship;
    }
  }
  LOG("no ship with matching id found");
  throw BattleshipException("no ship with matching id found");
}


const Player& game_state::getOtherPlayer(uuid playerId) {
  for (const Player& player : players) {
    if (player.getId() != playerId) {
      return player;
    }
  }
  LOG("did not find other player");
  throw BattleshipException("did not find other player");
}


const Player& game_state::getPlayer(uuid playerId) const {
  for (const Player& player : players) {
    if (player.getId() == playerId) {
      return player;
    }
  }
  LOG("no player with matching id found");
  throw BattleshipException("no player with matching id found");
}


bool game_state::shotIsLegal(uuid playerId, Coordinate position) {
  if (position.x < 0 || position.x >= 10) {
    return false;
  }
  if (position.y < 0 || position.y >= 10) {
    return false;
  }
  const PlayerGrid& grid = getPlayerGrid(playerId);
  if (grid.shotsFired[position.x][position.y]) {
    return false; // already fired at this tile
  }
  return true;
}

// all parameters after position are used to return info back to the caller
bool game_state::registerShot(uuid playerId, Coordinate position, bool *hit, Ship **hitShipPtr, bool *sunk, uuid *nextPlayerId) {

  LOG("Turn Number: " + std::to_string(turnNumber));
  LOG("Current Player: " + currentPlayerId.ToString());

  // check if the correct player is playing
  if (playerId != currentPlayerId) {
    LOG("It is not this players turn " + playerId.ToString());
    return false;
  }

  PlayerGrid shooterGrid  = playerGrids[0]; // grid of the shooter
  PlayerGrid targetGrid   = playerGrids[1]; // grid of the victim/target
  if (shooterGrid.playerId != playerId) {
    std::swap(shooterGrid, targetGrid);
  }
  const uuid targetPlayerId = targetGrid.playerId;

  // set default values
  *hit = false;
  *sunk = false;
  *hitShipPtr = new Ship(0, Coordinate(0,0), Ship::Orientation::Vertical, uuid());  // dummy ship

  // loop through all ships
  for (Ship& ship : targetGrid.shipsPlaced) {
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
  const int impact = *hit ? 2 : 1;  // 2=hit 1=miss;
  shooterGrid.shotsFired[position.x][position.y] = impact;
  targetGrid.shotsReceived[position.x][position.y] = impact;

  // determine next player
  *nextPlayerId = *hit ? playerId : targetPlayerId; // if shot was a hit, the current player goes again. otherwise switch
  currentPlayerId = *nextPlayerId;  // update current player
  LOG("next player: " + nextPlayerId->ToString());
  turnNumber++;
  return true;
}

bool game_state::updateBoards(const GameEvent &event) {
  LOG("updating board...");
  assert(playerGrids.size() == 1);
  PlayerGrid myGrid = playerGrids[0];
  // update my grid
  if (event.playerId == myGrid.playerId) {  // I called the shot
    LOG("This was my shot");
    myGrid.shotsFired[event.position.x][event.position.y] = event.hit ? 2 : 1;
  } else { // other player shot me
    LOG("This was the other players shot");
    // update shots
    myGrid.shotsReceived[event.position.x][event.position.y] = event.hit ? 2 : 1;
    // update my ships. only if there was a hit!! otherwise hitShip might be a dummy (every member 0)
    if (event.hit) {
      Ship &hitShip = getShip(myGrid.shipsPlaced, event.hitShip.getId()); // find out which of my local ships was hit
      hitShip.hit(event.position);
    }
  }
  // update current player
  currentPlayerId = event.nextPlayerId;
  LOG("finished updating board");
}

bool game_state::gameOver() {

  //assert(playerGrids.size() == 2 && "Number of grids is not 2. Cannot determine round win.");

  for (const PlayerGrid& grid: playerGrids) {
      bool lost = true;
      for (const Ship& ship : grid.shipsPlaced) {
        if (!ship.hasSunken()) {  // at least one ship still alive, therefore not lost yet
          lost = false;
          break;
        }
      }
      if (lost) {
        winner = getOtherPlayer(grid.playerId).getId(); // this player lost, so the other player is the winner
        state      = State::Finished;
        return true;
      }
  }
  return false;
}

uuid game_state::getWinner() {
  if (state == State::Finished) {
      return winner;
  } else {
      LOG("Asked for winner but game not finished");
      return uuid();
  }
}

const std::vector<Player>& game_state::get_players() const {
  return players;
}