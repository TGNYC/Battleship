#include "game_state/PlayerGrid.h"

#include "game_state/Ship.h"
#include "uuid.h"
#include <utility>
#include <vector>

PlayerGrid::PlayerGrid(uuid playerId, std::vector<Ship> shipsPlacement)
    : playerId(playerId), shipsPlaced(std::move(shipsPlacement)) {}
