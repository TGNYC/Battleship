#include "CallShot.h"

#include "../../game_state/Coordinate.h"
#include "../../uuid.h"
#include "ClientRequest.h"

CallShot::CallShot(uuid playerId, Coordinate position)
    : ClientRequest(playerId, RequestType::CallShot), m_position(position) {}

auto CallShot::getPosition() const -> Coordinate {
  return m_position;
}