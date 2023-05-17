//
// Created by nico on 03.05.23.
//

#include "GameEvent.h"
#include "game_state/Coordinate.h"
#include "game_state/Ship.h"
#include "uuid.h"

GameEvent::GameEvent(uuid playerId, Coordinate position, bool hit, bool sunk, Ship hitShip, uuid nextPlayerId)
    : ServerResponse(ResponseType::GameEvent), playerId(playerId), position(position), hit(hit), sunk(sunk),
      hitShip(Ship(hitShip.getLength(), hitShip.getPosition(), hitShip.getOrientation(), hitShip.getId())),
      nextPlayerId(nextPlayerId) {}