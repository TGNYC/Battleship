#ifndef VIEWGRID_H
#define VIEWGRID_H

#include <wx/wx.h>
#include "../../common/game_state/Ship.h"

class ViewGrid : public wxPanel{
public:
  enum GridType {own, opp};
  
  ViewGrid(wxWindow *parent, GridType type);

  wxPoint GetPosition() const {
    return _pos;
  }

  void showShips(const std::vector<Ship>& ships);
  void showShots(const int shots[10][10]);

private:
  wxPoint _pos;
  wxStaticBitmap **_grid;
  GridType _type;
  wxWindow *_parent;
};

#endif // VIEWGRID_H