//
// Created by robin on 28.04.23.
//

#ifndef BATTLESHIP_PLACEMENTGRID_H
#define BATTLESHIP_PLACEMENTGRID_H

#include <wx/wx.h>

class PlacementGrid : public wxPanel {
public:
  PlacementGrid(wxWindow *parent);

private:
  wxStaticBitmap **_grid;
};

#endif // BATTLESHIP_PLACEMENTGRID_H
