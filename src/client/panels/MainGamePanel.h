#ifndef MAINGAMEPANEL_H
#define MAINGAMEPANEL_H

#include <wx/wx.h>
#include <chrono>
#include "../../common/game_state/game_state.h"
#include "../../common/game_state/Player.h"
#include "../uiElements/ViewGrid.h"
#include "../uiElements/ShipPanel.h"
//#include "../AudioPlayer.h"

class MainGamePanel : public wxPanel {
public:
  /**
   * @brief Constructor for the main game panel.
   * Doesn't display anything, only the background color.
  */
  MainGamePanel(wxWindow *parent);
  /**
   * @brief Builds the game state.
   * @param gameState The game state.
   * @param ownId The id of the player who is using this client.
   * Displays the game state using ViewGrid and ShipPanel.
  */
  void buildGameState(game_state* gameState, uuid ownId);
  /**
   * @brief Displays the emote panel.
   * Not implemented yet. 
  */
  void buildEmoteList();
  /**
   * @brief Displays the turn indicator: It's ((playerName))'s turn
   * @param playerName The name of the player who's turn it is.
   * @param header The wxBoxSizer that contains the turn indicator.
  */
  void buildTurnIndicator(std::string playerName, wxBoxSizer *header);
  /**
   * @brief Function that is bound to the tiles of the opponent's view grid.
   * @param event The mouse event.
   * Makes sure that it's the player's turn and that the player can't shoot more than once per second.
   * Uses the position of the mouse pointer to find out which tile was clicked.
   * TODO: Calls the function shotIsLegal and sends callShot request to server.
  */
  void onMouseClick(wxMouseEvent& event);

private:
  game_state* _gameState;
  uuid _ownId;
  uuid _currentPlayer;
  ViewGrid* _ownViewGrid;
  ViewGrid* _oppViewGrid;
  ShipPanel* _ownShipPanel;
  ShipPanel* _oppShipPanel;
  std::chrono::system_clock::time_point _lastShot; // std::chrono::_V2::system_clock::time_point _lastShot;
};

#endif // MAINGAMEPANEL_H