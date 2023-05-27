#ifndef SETUPMANAGER_H
#define SETUPMANAGER_H

#include "../common/game_state/Ship.h"
#include <vector>
#include <wx/gdicmn.h>

class SetupManager {
public:
  /**
  * @brief constructor for SetupManager. Initializes ships and grid.
  */
  SetupManager();

  /**
  * @brief function places ship on grid and updates ship position
  * @param position of left-most or top-most cell of ship (depending on orientation)
  * @param ship pointer to ship that should be placed
  * @return true if ship was placed successfully and false if ship couldn't be placed
  */
  static bool placeShip(wxPoint &position, Ship *ship);

  /**
  * @brief getter for _grid
  * @return int pointer to _grid array
  */
  static int* getGrid();

  /**
  * @brief checks if all ships have been placed (= no longer at initial position)
  * @return true if all ships have been placed, false otherwise
  */
  static bool placedAllShips();

  static std::vector<Ship> _ships_placed;
  static Ship* _selectedShip;

private:
  static int *_grid;
};

#endif // SETUPMANAGER_H