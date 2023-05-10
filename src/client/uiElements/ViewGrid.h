#ifndef VIEWGRID_H
#define VIEWGRID_H

#include <wx/wx.h>
#include "../../common/game_state/Ship.h"

class ViewGrid : public wxPanel{
public:
  ViewGrid(wxWindow *parent, wxPoint pos);

  wxPoint GetPosition() const {
    return _pos;
  }
  wxStaticBitmap** getGrid() const {
    return _grid;
  }

  void showShips(const std::vector<Ship>& ships);
  void showShots(const int shots[10][10]);

private:
  wxPoint _pos;
  wxStaticBitmap **_grid;
};

#endif // VIEWGRID_H