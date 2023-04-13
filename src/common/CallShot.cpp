#include "CallShot.h"

#include "ClientRequest.h"
#include "Coordinate.h"
#include "uuid.h"

CallShot::CallShot(uuid playerId, Coordinate position)
    : ClientRequest(playerId, RequestType::CallShot), m_position(position) {}

auto CallShot::getPosition() const -> Coordinate {
  return m_position;
}