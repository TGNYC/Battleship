#ifndef BATTLESHIP_GAME_STATE_H
#define BATTLESHIP_GAME_STATE_H

#include "game_state/Player.h"
#include "game_state/PlayerGrid.h"
#include <vector>

class game_state {
public:
  enum class State {
    Starting,
    Playing,
    Finished
  };

  auto addPlayer(Player player) -> bool;
  auto addShips(uuid playerId, std::vector<Ship> shipPlacement) -> bool;

private:
  State                   m_state = State::Starting;
  std::vector<Player>     m_players;
  std::vector<PlayerGrid> m_playerGrid;
};

#endif // BATTLESHIP_GAME_STATE_H