//
// Created by nico on 03.05.23.
//

#ifndef BATTLESHIP_GAMEEVENT_H
#define BATTLESHIP_GAMEEVENT_H

#include "game_state/Coordinate.h"
#include "game_state/Ship.h"
#include "network/responses/ServerResponse.h"
#include "uuid.h"

/*!
 * A Game Event is emitted by the server if and only if a new shot was registered
 */
class GameEvent : public ServerResponse {
public:
  GameEvent(uuid playerId, Coordinate position, bool hit, bool sunk, Ship hitShip, uuid nextPlayerId);

  const uuid       playerId;     // id of the player who called the shot
  const Coordinate position;     // location of the shot
  const bool       hit  = false; // true if shot was a hit
  const bool       sunk = false; // not necessary for grid update, but useful for GUI reaction
  const Ship       hitShip;      // the ship that was hit (if there was a hit)
  const uuid       nextPlayerId; // id of the player who has to play next
};

#endif // BATTLESHIP_GAMEEVENT_H
