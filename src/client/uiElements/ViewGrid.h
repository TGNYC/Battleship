#ifndef VIEWGRID_H
#define VIEWGRID_H

#include <wx/wx.h>

class ViewGrid : public wxPanel{
public:
  ViewGrid(wxWindow *parent);

  wxStaticBitmap** getGrid() const {
    return _grid;
  }

  void placeShips(std::vector<Ship> ships);

private:
  wxStaticBitmap **_grid;
};

#endif // VIEWGRID_H