#ifndef SHIP_H
#define SHIP_H

#include "../uuid.h"
#include "Coordinate.h"
#include <vector>

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

  [[nodiscard]] auto setOrientation(Orientation orientation) -> void;
  [[nodiscard]] auto setPosition(Coordinate position) -> void;

  auto operator<=>(const Ship &) const = default;

  /*!
   * Hit detection. Processes a shot for an individual ship. Will update m_sunk and m_hits
   * @param shot coordinates of the shot called
   * @return true if ship was hit, false otherwise
   */
  bool hit(Coordinate shot);
  bool hasSunken() const;

private:
  int         m_length;
  Coordinate  m_position;
  Orientation m_orientation;
  uuid        m_id;
  bool              m_sunk;
  std::vector<bool> m_hits; // vector of size m_length storing hits
};

#endif // SHIP_H