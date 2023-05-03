//
// Created by nico on 03.05.23.
//

#ifndef BATTLESHIP_GAMEEVENT_H
#define BATTLESHIP_GAMEEVENT_H

#include "uuid.h"
#include "game_state/Coordinate.h"

/*
 * A Game Event is emitted by the server if and only if a new shot was called and accepted as legal
 */
class GameEvent {
private:
  uuid playerId;  // id of the player who called the shot
  Coordinate position;
  bool ship_hit = false;
  bool ship_sunk = false;
  bool game_over = false;
};

#endif // BATTLESHIP_GAMEEVENT_H
