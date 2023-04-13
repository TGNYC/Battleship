#ifndef STARTGAME_H
#define STARTGAME_H

#include "ClientRequest.h"
#include "Ship.h"
#include <vector>
class uuid;

class StartGame : public ClientRequest {
public:
  StartGame(uuid playerId, std::vector<Ship> ships);

  auto getShips() const -> std::vector<Ship>;

  auto operator<=>(const StartGame &) const = default;

private:
  std::vector<Ship> m_ships;
};

#endif // STARTGAME_H