#ifndef BATTLESHIP_GAME_STATE_H
#define BATTLESHIP_GAME_STATE_H

#include "game_state/Player.h"
#include "game_state/PlayerGrid.h"
#include "network/responses/GameEvent.h"
#include "Coordinate.h"
#include <vector>

class game_state {
public:
  enum class State {
    Starting,
    Playing,
    Finished
  };

  bool addPlayer(Player player);
  bool addShips(uuid playerId, std::vector<Ship> shipPlacement);
  Player getCurrentPlayer();
  bool removePlayer(uuid playerId);

  /*!
   * returns a const reference of the grid for e.g. display through UI
   */
  const PlayerGrid &getPlayerGrid(uuid playerId) const;

  /*!
   * @brief updates the boards after a game event happened.
   *
   * @param playerId id of the player who called the shot
   * @param position position of the shot
   */
  bool updateBoards(GameEvent event);
  bool shotIsLegal(uuid playerId, Coordinate position);
  bool wrapUpRound();

private:
  State                   m_state = State::Starting;
  std::vector<Player>     m_players;
  std::vector<PlayerGrid> m_playerGrids;  // length 1 (on client) or 2 (on server)

  unsigned int            m_num_players = 2;
  uuid                    currentPlayerId;  // specifies the id of the player whose turn it is
  unsigned int            turnNumber = 0; // specifies the current numbered turn
  bool                    isFinished = false; // specifies whether the game is finished or not
  bool                    serverSide = false; // indicates if this game_state is run server side
};

#endif // BATTLESHIP_GAME_STATE_H