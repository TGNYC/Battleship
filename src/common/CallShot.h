#ifndef CALLSHOT_H
#define CALLSHOT_H

#include "ClientRequest.h"
#include "Coordinate.h"
class uuid;

class CallShot : public ClientRequest {
public:
  CallShot(uuid playerId, Coordinate position);

  [[nodiscard]] auto getPosition() const -> Coordinate;

  auto operator<=>(const CallShot &) const = default;

private:
  Coordinate m_position;
};

#endif // CALLSHOT_H