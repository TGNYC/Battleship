#ifndef STARTGAME_H
#define STARTGAME_H

#include "../../game_state/Ship.h"
#include "ClientRequest.h"
#include <vector>
class uuid;

class StartGame : public ClientRequest {
public:
  StartGame(uuid playerId, std::vector<Ship> ships);

  [[nodiscard]] auto getShips() const -> std::vector<Ship>;

private:
  std::vector<Ship> _ships;
};

#endif // STARTGAME_H