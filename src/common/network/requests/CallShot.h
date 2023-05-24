#ifndef CALLSHOT_H
#define CALLSHOT_H

#include "ClientRequest.h"
#include "game_state/Coordinate.h"
class uuid;

class CallShot : public ClientRequest {
public:
  CallShot(uuid playerId, Coordinate position);

  [[nodiscard]] auto getPosition() const -> Coordinate;

private:
  Coordinate _position;
};

#endif // CALLSHOT_H