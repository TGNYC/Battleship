//
// Created by robin on 28.04.23.
//

#ifndef BATTLESHIP_PLACEMENTGRID_H
#define BATTLESHIP_PLACEMENTGRID_H

#include <wx/wx.h>

class PlacementGrid : public wxPanel {
public:
  PlacementGrid(wxWindow *parent);
  void OnMouseMotion(wxMouseEvent &event);
  void OnMouseClick(wxMouseEvent &event);
  void displayGrid();
  void highlightTiles(int CellX, int CellY);

  wxStaticBitmap** getGrid() const {
    return _grid;
  }

  int cellX_prev = -1;
  int cellY_prev = -1;

private:
  wxStaticBitmap **_grid;
};

#endif // BATTLESHIP_PLACEMENTGRID_H
