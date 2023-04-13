#ifndef SHIP_H
#define SHIP_H

#include "Coordinate.h"
#include "uuid.h"

class Ship {
public:
  enum class Orientation {
    Vertical,
    Horizontal
  };

  Ship(int length, Coordinate position, Orientation orientation, uuid id);

  auto getLength() const -> int;
  auto getPosition() const -> Coordinate;
  auto getOrientation() const -> Orientation;
  auto getId() const -> uuid;

  auto operator<=>(const Ship &) const = default;

private:
  int         m_length;
  Coordinate  m_position;
  Orientation m_orientation;
  uuid        m_id;
};

#endif // SHIP_H