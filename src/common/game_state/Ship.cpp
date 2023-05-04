#include "Ship.h"

Ship::Ship(int length, Coordinate position, Orientation orientation, uuid id)
    : m_length(length), m_position(position), m_orientation(orientation), m_id(id), m_sunk(false),
      m_hits(length, 0) {}

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

bool Ship::hit(Coordinate shot) {
  if (m_orientation == Orientation::Horizontal) {
    if (m_position.y == shot.y) { // same row
      if (m_position.x <= shot.x && m_position.x + m_length > shot.x) { // is hit
        m_hits.at( shot.x - m_position.x) = true;
        if (hasSunken()) m_sunk = true;
        return true;
      }
    }
  } else if (m_orientation == Orientation::Vertical) {
    if (m_position.x == shot.x) { // same column
      if (m_position.y <= shot.y && m_position.y + m_length > shot.y) { // is hit
        m_hits.at(shot.y - m_position.y) = true;
        if (hasSunken()) {
          m_sunk = true;
        }
        return true;
      }
    }
  }
  return false;
}

bool Ship::hasSunken() {
  if (m_sunk) return true;
  int sum = 0;
  for (const bool tile : m_hits) {
    sum += static_cast<int>(tile);
  }
  if (sum == m_length) {  // only true if all tiles of the ship were hit/true
    return true;
  } else {
    return false;
  }
}