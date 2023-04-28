//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H

#include "uuid.h"
#include <string>

class player {
public:
  player(uuid playerId, std::string player_name);

private:
  std::string m_name;
  uuid        m_id;
};

#endif // BATTLESHIP_PLAYER_H
