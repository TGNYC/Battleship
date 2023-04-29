#ifndef BATTLESHIP_PLAYERGRID_H
#define BATTLESHIP_PLAYERGRID_H

#include "game_state/Ship.h"
#include "uuid.h"
#include <vector>

class PlayerGrid {

public:
  PlayerGrid(uuid playerId, std::vector<Ship> shipsPlacement);

private:
  uuid              m_playerId;
  std::vector<Ship> m_shipsPlaced;
};

#endif // BATTLESHIP_PLAYERGRID_H