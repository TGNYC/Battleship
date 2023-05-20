//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H

#include "uuid.h"
#include <string>

class Player {
public:
  Player(uuid playerId, std::string player_name);
  auto getId() const -> uuid;
  auto getName() const -> std::string;

  bool operator==(const Player &) const = default;

private:
  uuid        _id;
  std::string _name;
};

#endif // BATTLESHIP_PLAYER_H
