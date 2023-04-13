#include "Ship.h"

Ship::Ship(int length, Coordinate position, Orientation orientation, uuid id)
    : length(length), position(position), orientation(orientation), id(id) {}

auto Ship::getLength() const -> int {
  return length;
}
auto Ship::getPosition() const -> Coordinate {
  return position;
}
auto Ship::getOrientation() const -> Orientation {
  return orientation;
}
auto Ship::getId() const -> uuid {
  return id;
}