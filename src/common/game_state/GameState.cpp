#include "GameState.h"
#include "Coordinate.h"
#include "Logger.h"
#include "Player.h"
#include <cassert>
#include <stdexcept>
#include <utility>

GameState::GameState(GameState::Type type) : _state(State::Starting), _type(type), _currentPlayerId(), _turnNumber(0) {

  _players     = std::vector<Player>();
  _playerGrids = std::vector<PlayerGrid>();
  LOG("Created GameState");
}

auto GameState::addPlayer(Player player) -> bool {
  // check if player is already added
  for (const Player &p : _players) {
    if (p.getId() == player.getId()) {
      return false;
    }
  }
  if (_players.size() >= 2) {
    return false;
  }
  LOG("Added Player to GameState: " + player.getName() + " " + player.getId().ToString());
  _players.push_back(player);
  return true;
}

bool GameState::removePlayer(Player player) {
  if (_state != State::Starting) {
    LOG("cannot remove player after game started");
    return false;
  }
  for (unsigned i = 0; i < _players.size(); ++i) {
    if (_players.at(i).getId() == player.getId()) {
      _players.erase(_players.begin() + i);
      return true;
    }
  }
  LOG("cannot remove non-existent player");
  return false;
}

auto GameState::addShips(uuid playerId, std::vector<Ship> shipPlacement) -> bool {
  // check for valid player id
  if (_players.empty() || (_players.at(0).getId() != playerId && _players.size() == 1) ||
      (_players.at(0).getId() != playerId && _players.at(1).getId() != playerId)) {
    return false;
  }
  // check if not already placed
  for (const PlayerGrid &grid : _playerGrids) {
    if (grid.playerId == playerId) {
      LOG("Ship placement for this player id already exists");
      return false;
    }
  }
  // create playerGrid and add it to the vector
  LOG("Added Ships of " + playerId.ToString() + " to GameState");
  _playerGrids.emplace_back(playerId, std::move(shipPlacement));
  return true;
}

bool GameState::start(uuid currentPlayerId) {
  if (_state != State::Starting) {
    LOG("Game state not in starting phase. Cannot start game.");
    return false;
  } else if (_players.size() != 2) {
    LOG("Number of players is not 2. Cannot start game.");
    return false;
  } else if (_type == Type::ServerState && _playerGrids.size() != 2) {
    LOG("Not 2 grids on server. Cannot start game.");
    return false;
  } else if (_type == Type::ClientState && _playerGrids.size() != 1) {
    LOG("Not 1 grid on client. Cannot start game.");
    return false;
  } else {
    this->_currentPlayerId = currentPlayerId;
    LOG("first to play: " + currentPlayerId.ToString());
    _state = State::Playing;
    LOG("Successfully started GameState");
    return true;
  }
}

uuid GameState::getCurrentPlayerId() {
  return _currentPlayerId;
}

const PlayerGrid &GameState::getPlayerGrid(uuid playerId) const {
  for (const PlayerGrid &grid : _playerGrids) {
    if (grid.playerId == playerId) {
      return grid;
    }
  }
  throw BattleshipException("Could not find grid for this player id");
}

Ship *GameState::getShip(std::vector<Ship> &ships, uuid shipId) {
  for (Ship &ship : ships) {
    if (ship.getId() == shipId) {
      return &ship;
    }
  }
  LOG("no ship with matching id found");
  return nullptr;
}

const Player *GameState::getOtherPlayer(uuid playerId) {
  for (const Player &player : _players) {
    if (player.getId() != playerId) {
      return &player;
    }
  }
  LOG("did not find other player");
  return nullptr;
}

const Player *GameState::getPlayer(uuid playerId) const {
  for (const Player &player : _players) {
    if (player.getId() == playerId) {
      return &player;
    }
  }
  LOG("no player with matching id found");
  return nullptr;
}

const std::vector<Player> &GameState::getPlayers() const {
  return _players;
}

const GameState::State &GameState::getState() const {
  return _state;
}

const std::array<bool, 5> &GameState::getOppShipSunk() {
  return _oppShipSunk;
}

bool GameState::shotIsLegal(uuid playerId, Coordinate position) {
  if (_state != State::Playing) {
    LOG("State is not set to playing");
    return false;
  }
  // check if the correct player is playing
  if (playerId != _currentPlayerId) {
    LOG("It is not this players turn " + playerId.ToString());
    return false;
  }
  if (position.x < 0 || position.x >= 10) {
    return false;
  }
  if (position.y < 0 || position.y >= 10) {
    return false;
  }
  const PlayerGrid &grid = getPlayerGrid(playerId);
  if (grid.shotsFired[position.x][position.y]) {
    return false; // already fired at this tile
  }
  return true;
}

// all parameters after position are used to return info back to the caller
bool GameState::registerShot(uuid playerId, Coordinate position, bool *hit, Ship **hitShipPtr, bool *sunk,
                             uuid *nextPlayerId) {
  assert(_type == Type::ServerState && _playerGrids.size() == 2);
  LOG("Turn Number: " + std::to_string(_turnNumber));
  LOG("Current Player: " + _currentPlayerId.ToString());

  if (!shotIsLegal(playerId, position)) {
    LOG("illegal shot");
    return false;
  }

  PlayerGrid &shooterGrid = _playerGrids[0]; // grid of the shooter
  PlayerGrid &targetGrid  = _playerGrids[1]; // grid of the victim/target
  if (shooterGrid.playerId != playerId) {
    std::swap(shooterGrid, targetGrid);
  }
  const uuid targetPlayerId = targetGrid.playerId;

  // set default values
  *hit        = false;
  *sunk       = false;
  *hitShipPtr = new Ship(0, {0, 0}, Ship::Orientation::Vertical, uuid()); // dummy ship

  // loop through all ships
  for (Ship &ship : targetGrid.shipsPlaced) {
    if (ship.hit(position)) {
      *hit        = true;
      *hitShipPtr = &ship;
      if (ship.hasSunken()) {
        LOG("ship sunk");
        *sunk = true;
      }
      break; // if a ship was hit, we can stop the loop
    }
  }

  // update server side game state
  const int impact                                 = *hit ? 2 : 1; // 2=hit 1=miss;
  shooterGrid.shotsFired[position.x][position.y]   = impact;
  targetGrid.shotsReceived[position.x][position.y] = impact;

  // determine next player
  *nextPlayerId =
      *hit ? playerId : targetPlayerId; // if shot was a hit, the current player goes again. otherwise switch
  _currentPlayerId = *nextPlayerId;     // update current player
  LOG("next player: " + nextPlayerId->ToString());
  _turnNumber++;
  return true;
}

bool GameState::updateBoards(const GameEvent &event) {
  LOG("updating board...");
  assert(_type == Type::ClientState && _playerGrids.size() == 1);
  auto &myGrid = _playerGrids[0];
  // update my grid
  if (event.playerId == myGrid.playerId) { // I called the shot
    LOG("This was my shot");
    myGrid.shotsFired[event.position.x][event.position.y] = event.hit ? 2 : 1;
    if (event.sunk) {
      updateOppShipSunk(event.hitShip);
    }
  } else { // other player shot me
    LOG("This was the other players shot");
    // update shots
    myGrid.shotsReceived[event.position.x][event.position.y] = event.hit ? 2 : 1;
    // update my ships. only if there was a hit!! otherwise hitShip might be a dummy (every member 0)
    if (event.hit) {
      Ship *hitShip = getShip(myGrid.shipsPlaced, event.hitShip.getId()); // find out which of my local ships was hit
      if (hitShip != nullptr) {
        hitShip->hit(event.position);
      } else {
        LOG("invalid ship id");
      }
    }
  }

  LOG("" + std::to_string(_oppShipSunk[0]) + " " + std::to_string(_oppShipSunk[1]) + " " +
      std::to_string(_oppShipSunk[2]) + " " + std::to_string(_oppShipSunk[3]) + " " + std::to_string(_oppShipSunk[4]));

  // update current player
  _currentPlayerId = event.nextPlayerId;
  LOG("finished updating board");
  return true;
}

bool GameState::updateOppShipSunk(const Ship &hitShip) {
  switch (hitShip.getLength()) {
  case 2:
    _oppShipSunk[4] = true;
    return true;
  case 3:
    // we have 2 ships of length 3, thus just cross them one after the other
    if (_oppShipSunk[3]) {
      _oppShipSunk[2] = true;
    } else {
      _oppShipSunk[3] = true;
    }
    return true;
  case 4:
    _oppShipSunk[1] = true;
    return true;
  case 5:
    _oppShipSunk[0] = true;
    return true;
  default:
    LOG("invalid ship length");
    return false;
  }
}

bool GameState::gameOver() {
  assert(_type == Type::ServerState);
  for (const PlayerGrid &grid : _playerGrids) {
    bool lost = true;
    for (const Ship &ship : grid.shipsPlaced) {
      if (!ship.hasSunken()) { // at least one ship still alive, therefore not lost yet
        lost = false;
        break;
      }
    }
    if (lost) {
      _winner = getOtherPlayer(grid.playerId)->getId(); // this player lost, so the other player is the _winner
      _state  = State::Finished;
      return true;
    }
  }
  return false;
}

uuid GameState::getWinner() {
  if (_state == State::Finished) {
    return _winner;
  } else {
    LOG("Asked for _winner but game not finished");
    return uuid();
  }
}

void GameState::finish() {
  _state = State::Finished;
}
