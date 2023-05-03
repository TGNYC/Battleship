#include "SetupManager.h"
#include "GameController.h"
#include "game_state/Coordinate.h"


SetupManager::SetupManager() {
  // generate ships
  _ships_placed.emplace_back(Ship(5, Coordinate{-1,-1}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _ships_placed.emplace_back(Ship(4, Coordinate{-1,-1}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _ships_placed.emplace_back(Ship(3, Coordinate{-1,-1}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _ships_placed.emplace_back(Ship(3, Coordinate{-1,-1}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _ships_placed.emplace_back(Ship(2, Coordinate{-1,-1}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _selectedShip = nullptr;
}

bool SetupManager::placeShip(wxPoint &position, Ship *ship) {
  // access setuppanel
  auto *visualGrid = GameController::getSetupPanel()->getPlacementGrid()->getGrid();

  // check in grid if position is valid
  const int length = ship->getLength();
  auto orientation = ship->getOrientation();

  const int cellX = position.x / 40;
  const int cellY = position.y / 40;

  if (orientation == Ship::Orientation::Horizontal) {
    if (cellX + length > 10) {
    return false;
    }
  }
  else {
    if (cellY + length > 10) {
    return false;
    }
  }
}