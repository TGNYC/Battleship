//
// Created by nico on 03.05.23.
//

#include "GameEvent.h"
const uuid &GameEvent::getPlayerId() const {
  return playerId;
}
const Coordinate &GameEvent::getPosition() const {
  return position;
}
