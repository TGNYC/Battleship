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
  const PlayerGrid& getPlayerGrid(uuid playerId) const;

  /*!
   * returns a reference to the ship with the specified id
   */
  Ship& getShip(std::vector<Ship>& ships, uuid shipId);

  /*!
   * returns the id of the player who has NOT the id specified as parameter
   * @param playerId
   * @return id of the other player. "Error" if no other player found.
   */
  uuid getOtherPlayer(uuid playerId);
  /*!
   * checks if a called shot is a legal move
   * @param playerId ID of the player calling the shot
   * @param position location of the shot
   * @return
   */
  bool shotIsLegal(uuid playerId, Coordinate position);

  /*!
   * Function to register a shot on the server side and process the results
   *
   * All arguments from *hit on are to used to return info back to the caller (the gameInstance)
   * Warning: The double pointer for the ship is intentional. Don't change please!
   *
   * @param playerId ID of the player who called the shot
   * @param position location of the shot
   *
   * @param hit holds info on whether the shot was a hit
   * @param hitShip holds info on the (potentially) hit ship for the caller to extract (and emit a GameEvent)
   * Turns the pointer to nullptr if no hit is false.
   * @param sunk holds info on whether the hit ship has sunk
   * @param nextPlayerId id of the player who has to play next
   * @return true if the shot was registered properly, false if a problem occured
   */
  bool registerShot(uuid playerId, Coordinate position, bool *hit, Ship **hitShipPtr, bool *sunk, uuid *nextPlayerId);

  /*!
   * @brief updates the client side boards after a game event happened.
   * @param event
   */
  bool updateBoards(GameEvent& event);

  /*!
   * Checks if the game is over meaning all ships of one player are sunk
   * @param winner id of the winning player. will be "DiniMueter" if game is not over.
   * @return true if game is over. false if game is not over
   */
  bool gameOver(uuid *winner);

  //bool wrapUpRound();

private:
  State                   m_state = State::Starting;
  std::vector<Player>     m_players;
  std::vector<PlayerGrid> m_playerGrids;  ///< holds 1 grid on client and 2 grids on server

  //unsigned int            m_num_players = 2;
  uuid                    currentPlayerId;  // specifies the id of the player whose turn it is
  unsigned int            turnNumber = 0; // specifies the current numbered turn
  bool                    isFinished = false; // specifies whether the game is finished or not
  bool                    serverSide = false; // indicates if this game_state is run server side
};

#endif // BATTLESHIP_GAME_STATE_H