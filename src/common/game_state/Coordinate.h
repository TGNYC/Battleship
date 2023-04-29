#ifndef BATTLESHIP_COORDINATE_H
#define BATTLESHIP_COORDINATE_H

#include <compare>

struct Coordinate {
  int x = 0;
  int y = 0;

  auto operator<=>(const Coordinate &) const = default;
};

#endif // BATTLESHIP_COORDINATE_H