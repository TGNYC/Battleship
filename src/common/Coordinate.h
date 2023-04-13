#ifndef COORDINATE_H
#define COORDINATE_H

#include <compare>

struct Coordinate {
  int x = 0;
  int y = 0;

  auto operator<=>(const Coordinate &) const = default;
};

#endif // COORDINATE_H