//
// Created by robin on 18.05.23.
//

#ifndef BATTLESHIP_QUITGAMEEVENT_H
#define BATTLESHIP_QUITGAMEEVENT_H

#include "ServerResponse.h"
#include "uuid.h"

class QuitGameEvent : public ServerResponse {
  public:
    explicit QuitGameEvent(uuid quitPlayerId);

    const uuid quitPlayerId; // id of the player who quit
};

#endif // BATTLESHIP_QUITGAMEEVENT_H
