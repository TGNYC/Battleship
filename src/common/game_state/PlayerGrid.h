#ifndef BATTLESHIP_PLAYERGRID_H
#define BATTLESHIP_PLAYERGRID_H

#include "game_state/Ship.h"
#include "uuid.h"
#include <vector>

/*!
 * Data container to store ocean grid info. A grid always belongs to one player (the one who has his ships on this grid)
 */
class PlayerGrid {

  // members of grid public so GameState can easily modify them.
public:
  PlayerGrid(uuid playerId, std::vector<Ship> shipsPlacement);

  uuid              playerId;        ///< id of owner of this grid
  std::vector<Ship> shipsPlaced;     ///< vector of all ships placed on this grid
  int shotsReceived[10][10] = {{0}}; ///< shots received by this grid. 0 = tile not shot, 1 = miss, 2 = hit
  int shotsFired[10][10]    = {{0}}; ///< shots fired by this player. 0 = tile not shot, 1 = miss, 2 = hit
};

#endif // BATTLESHIP_PLAYERGRID_H