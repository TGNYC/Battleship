#ifndef BATTLESHIP_GAMESTATE_H
#define BATTLESHIP_GAMESTATE_H

#include "Coordinate.h"
#include "game_state/Player.h"
#include "game_state/PlayerGrid.h"
#include "network/responses/GameEvent.h"
#include <vector>

/*
 * USAGE SERVER
 * -- setup --
 * Call constructor
 * addPlayer() for both players
 * addShips() for both players
 * determine player who goes first. send startGame response to clients with this info
 * start()
 *
 * -- playing --
 * whenever a callShot request is received: check shotIsLegal(), then call registerShot()
 * send a gameEvent to clients with the info provided by registerShot() -> see function documentation for details
 * check gameOver() to see if game is finished
 * if yes, call getWinner() to receive _winner id. then send corresponding event to clients
 *
 * USAGE CLIENT
 * -- setup --
 * Call constructor
 * addPlayer() for both players (needs to receive other player from server somehow)
 * addShips() ONLY FOR THE LOCAL PLAYER
 * wait for startGame response which includes id of player who goes first
 * start()
 *
 * -- playing --
 * when receiving a gameEvent: updateBoards(event)
 * use getPlayerGrid() to get grid data for UI update
 * use getCurrentPlayerId() to see if it is your turn
 * check shotIsLegal() before sending a callShot Request
 */

class GameState {
public:
  /*!
   * Enum indicating the phase of the game state. Must be switched to Playing before first move is made
   */
  enum class State {
    Starting,
    Playing,
    Finished
  };

  /*!
   * Enum indicating whether a server side game state is being stored or a client side game state
   */
  enum class Type {
    ServerState,
    ClientState
  };

  /*!
   * Constructor setting initial values
   * @param type defines if this is a server side or client side state
   */
  GameState(GameState::Type type);

  /*!
   * Adds a player to the game state
   * @param player the player object
   * @return true if player was added successfully, false if a problem occurred.
   */
  bool addPlayer(Player player);

  /*!
   * Creates a new playerGrid from a full ship placement
   * @param playerId id of the player who placed the ships and owns the board
   * @param shipPlacement a vector containing all ships
   * @return true if grid was created successfully, false if a problem occurred.
   */
  bool addShips(uuid playerId, std::vector<Ship> shipPlacement);

  /*!
   * Switches the game state from State::Starting to State::Playing
   * @pre Two players were added to the state. Grids were added (1 for clients, 2 for servers).
   * @param currentPlayerId id of the player who will go first
   * @return true if the game was started, false if a problem occurred. Check log file for details.
   */
  bool start(uuid currentPlayerId);

  /*!
   *   getter for the id of the player whose turn it currently is
   */
  uuid getCurrentPlayerId();

  /*!
   * returns a const reference of the grid for e.g. display through UI
   */
  const PlayerGrid &getPlayerGrid(uuid playerId) const;

  /*!
   * returns a vector of all the players (2)
   */
  const std::vector<Player> &getPlayers() const;

  /*!
   * returns a reference to the ship with the specified id from a given vector of ships
   */
  Ship &getShip(std::vector<Ship> &ships, uuid shipId);

  /*!
   * returns the name of the player with the specified id
   */
  const Player &getPlayer(uuid playerId) const;

  /*!
   * returns the id of the player who has NOT the id specified as parameter
   * @param playerId
   * @return id of the other player. "Error" if no other player found.
   */
  const Player &getOtherPlayer(uuid playerId);

  /*!
   * returns the current state of the game (starting, playing, finished)
   */
  const State &getState() const;

  /*!
   * returns an array of bool which indicates which opponent ships were already sunk.
   * used for crossing out ships at the bottom of the UI
   */
  std::array<bool, 5> &getOppShipSunk();

  /*!
   * checks if a called shot is a legal move
   * @param playerId ID of the player calling the shot
   * @param position location of the shot
   * @return
   */
  bool shotIsLegal(uuid playerId, Coordinate position);

  /*!
   * Function to register a shot ON THE SERVER SIDE and process the results
   *
   * All arguments from *hit on are to used to return info back to the caller (in this case to gameInstance)
   * Warning: The double pointer for the ship is intentional. Don't change please!
   *
   * @param playerId ID of the player who called the shot
   * @param position location of the shot
   *
   * @param hit holds info on whether the shot was a hit
   * @param hitShip holds info on the (potentially) hit ship for the caller to extract (and emit a GameEvent)
   * Turns the pointer to nullptr if no hit is false.
   * @param sunk holds info on whether the hit ship has sunk
   * @param nextPlayerId holds id of the player who has to play next
   * @return true if the shot was registered properly, false if a problem occured
   */
  bool registerShot(uuid playerId, Coordinate position, bool *hit, Ship **hitShipPtr, bool *sunk, uuid *nextPlayerId);

  /*!
   * @brief updates the CLIENT SIDE boards after a game event happened. //TODO rename to updateState or updateGrid
   * @param event
   */
  bool updateBoards(const GameEvent &event);

  /*!
   * Checks if the game is over meaning all ships of one player are sunk
   * @param winner id of the winning player. will be "0" if game is not over.
   * @return true if game is over. false if game is not over
   */
  bool gameOver();
  /*!
   * Returns the winner if the game is over. Should only be called after gameOver() returned true.
   * @return id of winner. null-uuid if game is not over
   */
  uuid getWinner();

  /*!
   * sets gamestate to Finished. For a next game, a new gamestate should be created. Thus this does not reset everything.
   */
  void finish();

private:
  State                   _state; // currently unused. will be needed later
  Type                    _type;  ///< indicates if this GameState is run server side or client side
  std::vector<Player>     _players;  ///< keeps track of players (2)
  std::vector<PlayerGrid> _playerGrids; ///< holds 1 grid on client and 2 grids on server
  std::array<bool, 5>     _oppShipSunk{};  ///< helper for UI to cross out enemy ships

  uuid         _currentPlayerId; // specifies the id of the player whose turn it is
  unsigned int _turnNumber;      // specifies the current numbered turn
  uuid         _winner;
};

#endif // BATTLESHIP_GAMESTATE_H