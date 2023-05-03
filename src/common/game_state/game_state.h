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
  // updates the boards after a game event happened.
  // on client side this function is called when the network manager receives a GameEvent response from the server
  // on server side this function is called after when the request_handler receives a callShot request and creates a gameEvent based on that shot.
  bool updateBoards(GameEvent event);
  bool shotIsLegal(uuid playerId, Coordinate position);
  bool isHit(uuid playerId, Coordinate position); // returns true if the called shot would hit

private:
  State                   m_state = State::Starting;
  std::vector<Player>     m_players;
  std::vector<PlayerGrid> m_playerGrid;

  unsigned int            m_num_players = 2;
  uuid                    currentPlayerId;  // specifies the id of the player whose turn it is
  unsigned int            turnNumber = 0; // specifies the current numbered turn
  bool                    isFinished = false; // specifies whether the game is finished or not
};

#endif // BATTLESHIP_GAME_STATE_H