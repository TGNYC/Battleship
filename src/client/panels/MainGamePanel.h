#ifndef MAINGAMEPANEL_H
#define MAINGAMEPANEL_H

#include <wx/wx.h>
#include "../../common/game_state/game_state.h"
#include "../../common/game_state/Player.h"
#include "../uiElements/ViewGrid.h"

class MainGamePanel : public wxPanel {
public:
  MainGamePanel(wxWindow *parent);
  void buildGameState(game_state* gameState, Player* me);
  void buildEmoteList();
  void buildTurnIndicator();

private:
  ViewGrid* _ownViewGrid;
  ViewGrid* _opponentViewGrid;
};

#endif // MAINGAMEPANEL_H