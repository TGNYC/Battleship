#include "Ship.h"

Ship::Ship(int length, Coordinate position, Orientation orientation, uuid id)
    : m_length(length), m_position(position), m_orientation(orientation), m_id(id) {}

auto Ship::getLength() const -> int {
  return m_length;
}
auto Ship::getPosition() const -> Coordinate {
  return m_position;
}
auto Ship::getOrientation() const -> Orientation {
  return m_orientation;
}
auto Ship::getId() const -> uuid {
  return m_id;
}
auto Ship::setOrientation(Ship::Orientation orientation) -> void {
  m_orientation = orientation;
}
auto Ship::setPosition(Coordinate position) -> void {
  m_position = position;
}
