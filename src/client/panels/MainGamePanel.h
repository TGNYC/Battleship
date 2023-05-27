#ifndef MAINGAMEPANEL_H
#define MAINGAMEPANEL_H

#include "../../common/game_state/Player.h"
#include "../../common/network/responses/EmoteEvent.h"
#include "../uiElements/EmotePanel.h"
#include "../uiElements/EmotePopup.h"
#include "../uiElements/ShipPanel.h"
#include "../uiElements/ViewGrid.h"
#include "game_state/GameState.h"
#include <wx/wx.h>

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
  void buildGameState(GameState *gameState, uuid ownId);

  /**
   * @brief Displays the emote sent by the other player.
   * @param emote The emote type that was sent.
   * Not implemented yet.
  */
  void displayEmote(EmoteType emote);

private:
  wxBoxSizer* _mainWindow;
  wxBoxSizer* _emoteWindow;
  GameState* _gameState;
  uuid _ownId;
  uuid _currentPlayer;
  ViewGrid* _ownViewGrid;
  ViewGrid* _oppViewGrid;
  ShipPanel* _ownShipPanel;
  ShipPanel* _oppShipPanel;
  EmotePanel* _emotePanel;
  wxStaticText *_turnText;
  EmotePopup* _currentEmote = nullptr;
};

#endif // MAINGAMEPANEL_H