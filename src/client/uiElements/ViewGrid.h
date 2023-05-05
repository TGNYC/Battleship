#ifndef VIEWGRID_H
#define VIEWGRID_H

#include <wx/wx.h>
#include "../../common/game_state/Ship.h"
#include "../../common/game_state/PlayerGrid.h"

class ViewGrid : public wxPanel{
public:
  ViewGrid(wxWindow *parent, wxPoint pos, PlayerGrid* playerGrid);

  wxStaticBitmap** getGrid() const {
    return _grid;
  }

  void showShips();
  void showShots();

  wxPoint GetPosition() const {
    return _pos;
  }

private:
  wxPoint _pos;
  wxStaticBitmap **_grid;
  PlayerGrid* _playerGrid;
};

#endif // VIEWGRID_H