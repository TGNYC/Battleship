#ifndef BATTLESHIP_GAMESTATE_H
#define BATTLESHIP_GAMESTATE_H

#include "game_state/Player.h"
#include "game_state/PlayerGrid.h"
#include <vector>

class GameState {
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

#endif // BATTLESHIP_GAMESTATE_H