//
// Created by nico on 03.05.23.
//

#ifndef BATTLESHIP_GAMEEVENT_H
#define BATTLESHIP_GAMEEVENT_H

#include "uuid.h"
#include "game_state/Coordinate.h"
#include "game_state/Ship.h"

/*
 * A Game Event is emitted by the server if and only if a new shot was called and accepted as legal
 */
class GameEvent {
public:
  uuid playerId; // id of the player who called the shot
  Coordinate position;
  bool hit = false;
  bool sunk = false;
  Ship hitShip; // the ship that was hit (if there was a hit)
  uuid nextPlayerId; // id of the player who has to play next
  // TODO include ship info if ship has been hit or sunk
};

#endif // BATTLESHIP_GAMEEVENT_H
