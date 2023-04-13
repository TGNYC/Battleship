#ifndef CALLSHOT_H
#define CALLSHOT_H

#include "ClientRequest.h"
#include "Coordinate.h"
class uuid;

class CallShot : public ClientRequest {
public:
  CallShot(uuid playerId, Coordinate position);

  auto getPosition() const -> Coordinate;

  auto operator<=>(const CallShot &) const = default;

private:
  Coordinate position;
};

#endif // CALLSHOT_H