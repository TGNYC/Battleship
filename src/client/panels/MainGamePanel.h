#ifndef MAINGAMEPANEL_H
#define MAINGAMEPANEL_H

#include <wx/wx.h>
#include "../../common/game_state/game_state.h"
#include "../../common/game_state/Player.h"
#include "../uiElements/ViewGrid.h"
#include "../uiElements/ShipPanel.h"

class MainGamePanel : public wxPanel {
public:
  MainGamePanel(wxWindow *parent);
  void buildGameState(game_state* gameState, Player* me);
  void buildEmoteList();
  void buildTurnIndicator();

private:
  game_state* _gameState;
  Player* _me;
  ViewGrid* _ownViewGrid;
  ViewGrid* _oppViewGrid;
  ShipPanel* _ownShipPanel;
  ShipPanel* _oppShipPanel;
};

#endif // MAINGAMEPANEL_H