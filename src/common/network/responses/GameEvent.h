//
// Created by nico on 03.05.23.
//

#ifndef BATTLESHIP_GAMEEVENT_H
#define BATTLESHIP_GAMEEVENT_H

#include "uuid.h"
#include "game_state/Coordinate.h"
#include "game_state/Ship.h"

/*!
 * A Game Event is emitted by the server if and only if a new shot was registered
 */
class GameEvent {
public:
  uuid playerId; // id of the player who called the shot
  Coordinate position;  // location of the shot
  bool hit = false; // true if shot was a hit
  bool sunk = false;  // not necessary for grid update, but useful for GUI reaction
  Ship hitShip; // the ship that was hit (if there was a hit)
  uuid nextPlayerId; // id of the player who has to play next
};

#endif // BATTLESHIP_GAMEEVENT_H
