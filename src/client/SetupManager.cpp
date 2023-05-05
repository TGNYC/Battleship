#include "SetupManager.h"
#include "GameController.h"
#include "game_state/Coordinate.h"

//std::vector<Ship> SetupManager::_ships_placed;
//Ship* SetupManager::_selectedShip;
int * SetupManager::_grid;

SetupManager::SetupManager() {
  // generate ships
  _ships_placed.emplace_back(Ship(5, Coordinate{-1,-1}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _ships_placed.emplace_back(Ship(4, Coordinate{-1,-1}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _ships_placed.emplace_back(Ship(3, Coordinate{-1,-1}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _ships_placed.emplace_back(Ship(3, Coordinate{-1,-1}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _ships_placed.emplace_back(Ship(2, Coordinate{-1,-1}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _selectedShip = nullptr;

  _grid = new int[100];

  // init grid to 0
  for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
          _grid[i*10+j] = 0;
        }
  }

}

/**
 * @brief function places ship on grid and updates ship position
 * @param position of left-most or top-most cell of ship (depending on orientation)
 * @param ship pointer to ship that should be placed
 * @return true if ship was placed successfully and false if ship couldn't be placed
 */
bool SetupManager::placeShip(wxPoint &position, Ship *ship) {
  if(ship == nullptr)
        return false;

  // access setuppanel
  auto *visualGrid = GameController::getSetupPanel()->getPlacementGrid()->getGrid();

  // check in grid if position is valid
  const int length      = ship->getLength();
  auto      orientation = ship->getOrientation();

  const int cellX = position.x / 40;
  const int cellY = position.y / 40;
  // column-major order
  int idx = cellX*10 + cellY;

  // check if ship would be out of bounds
  if ((orientation == Ship::Orientation::Horizontal && cellX + length > 10) ||
      (orientation == Ship::Orientation::Vertical && cellY + length > 10)) {
        return false;
  }

  // check if ship would overlap with another ship
  bool overlap = false;
  for (int i = 0; i < length; ++i) {
        if (orientation == Ship::Orientation::Horizontal)
          overlap = overlap || _grid[idx] != 0;
        else
          overlap = overlap || _grid[idx] != 0;
  }
  if (overlap)
        return false;

  // get idx of ship in _ships_placed
  for(int i = 0; i < _ships_placed.size(); ++i) {
        if(_ships_placed[i].getId() == ship->getId()) {
          // update ship position
          _ships_placed[i].setPosition(Coordinate{cellX, cellY});
          for(int j = 0; j < length; ++j) { // set ship id in grid array
            if(orientation == Ship::Orientation::Horizontal)
              _grid[(cellX+j)*10 + cellY] = i + 1;
            else
              _grid[(cellX)*10 + cellY+ j] = i + 1;
          }
          break;
        }
  }

  // print grid (debug)
  for(int i = 0; i < 10; ++i) {
          for(int j = 0; j < 10; ++j) {
          std::cout << _grid[i+j*10] << " ";
          }
          std::cout << std::endl;
  }




  return true;
}
int *SetupManager::getGrid() {
  return _grid;
}
