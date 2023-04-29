#ifndef SETUPMANAGER_H
#define SETUPMANAGER_H

#include "../common/game_state/Ship.h"
#include <vector>

class SetupManager {
public:
  SetupManager();


private:
  std::vector<Ship> _ships_placed;

};



#endif // SETUPMANAGER_H