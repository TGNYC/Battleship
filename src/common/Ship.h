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

  [[nodiscard]] auto getLength() const -> int;
  [[nodiscard]] auto getPosition() const -> Coordinate;
  [[nodiscard]] auto getOrientation() const -> Orientation;
  [[nodiscard]] auto getId() const -> uuid;

  auto operator<=>(const Ship &) const = default;

private:
  int         m_length;
  Coordinate  m_position;
  Orientation m_orientation;
  uuid        m_id;
};

#endif // SHIP_H