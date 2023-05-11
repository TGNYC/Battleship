#ifndef BATTLESHIP_STARTGAMESUCCESS_H
#define BATTLESHIP_STARTGAMESUCCESS_H

#include "game_state/Player.h"
#include "network/responses/ServerResponse.h"
#include <vector>

class StartGameSuccess : public ServerResponse {
public:
  const std::vector<Player> players;
  const uuid                startingPlayerId;

  StartGameSuccess(std::vector<Player> players, uuid startingPlayerId);
};

#endif // BATTLESHIP_STARTGAMESUCCESS_H