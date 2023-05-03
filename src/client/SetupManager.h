#ifndef SETUPMANAGER_H
#define SETUPMANAGER_H

#include "../common/game_state/Ship.h"
#include <vector>
#include <wx/gdicmn.h>

class SetupManager {
public:
  SetupManager();
  static std::vector<Ship> _ships_placed;
  static Ship* _selectedShip;

  static bool placeShip(wxPoint &position, Ship *ship);

private:
  static int _grid[10][10];
};



#endif // SETUPMANAGER_H