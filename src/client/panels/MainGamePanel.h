#ifndef MAINGAMEPANEL_H
#define MAINGAMEPANEL_H

#include <wx/wx.h>
#include <chrono>
#include "../../common/game_state/game_state.h"
#include "../../common/game_state/Player.h"
#include "../uiElements/ViewGrid.h"
#include "../uiElements/ShipPanel.h"
#include "../AudioPlayer.h"

class MainGamePanel : public wxPanel {
public:
  MainGamePanel(wxWindow *parent);
  void buildGameState(game_state* gameState, uuid ownId, uuid currentPlayer);
  void buildEmoteList();
  void buildTurnIndicator();

  void onMouseClick(wxMouseEvent& event);

private:
  game_state* _gameState;
  uuid _ownId;
  uuid _currentPlayer;
  ViewGrid* _ownViewGrid;
  ViewGrid* _oppViewGrid;
  ShipPanel* _ownShipPanel;
  ShipPanel* _oppShipPanel;
  std::chrono::_V2::system_clock::time_point _lastShot;
};

#endif // MAINGAMEPANEL_H