#include "SetupManager.h"


SetupManager::SetupManager() {
  // generate ships
  _ships_placed.emplace_back(Ship(5, Coordinate(-1,-1), Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _ships_placed.emplace_back(Ship(4, Coordinate(-1,-1), Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _ships_placed.emplace_back(Ship(3, Coordinate(-1,-1), Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _ships_placed.emplace_back(Ship(3, Coordinate(-1,-1), Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
  _ships_placed.emplace_back(Ship(2, Coordinate(-1,-1), Ship::Orientation::Horizontal, uuid::generateRandomUuid()));
}
