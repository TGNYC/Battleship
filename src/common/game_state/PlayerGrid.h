#ifndef BATTLESHIP_PLAYERGRID_H
#define BATTLESHIP_PLAYERGRID_H

#include "game_state/Ship.h"
#include "uuid.h"
#include <vector>

class PlayerGrid {

// members of grid public so game_state can easily modify them.
// const getter for grid also allows UI to access members without having to call 4 different getters
public:
  PlayerGrid(uuid playerId, std::vector<Ship> shipsPlacement);
  uuid              m_playerId;
  std::vector<Ship> m_shipsPlaced;
  int               shotsReceived[10][10] = {0};  // 0: tile not shot | 1: miss | 2: hit
  int               shotsFired[10][10] = {0};     // 0: tile not shot | 1: miss | 2: hit
};

#endif // BATTLESHIP_PLAYERGRID_H