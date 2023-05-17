#ifndef BATTLESHIP_GAMEOVEREVENT_H
#define BATTLESHIP_GAMEOVEREVENT_H

#include "network/responses/ServerResponse.h"
#include "uuid.h"

class GameOverEvent : public ServerResponse {
public:
  explicit GameOverEvent(uuid winnerPlayerId);

  const uuid winnerPlayerId; // id of the wining player
};

#endif // BATTLESHIP_GAMEOVEREVENT_H