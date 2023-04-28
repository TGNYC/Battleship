//
// Created by robin on 28.04.23.
//

#include "PlacementGrid.h"
#include <wx/wx.h>

PlacementGrid::PlacementGrid(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 400)) {
  wxColor backgroundColor = wxColor(255, 255, 0);
  this->SetBackgroundColour(backgroundColor);

  wxStaticBitmap* grid[10][10];
  wxBitmap emptyTile = wxBitmap(wxImage("../assets/empty_tile.png"));
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      grid[i][j] = new wxStaticBitmap(parent, wxID_ANY, emptyTile, wxPoint(i*40, j*40), wxSize(40, 40));
    }
  }

  wxBitmap gridLines = wxBitmap(wxImage("../assets/grid_lines.png"));
  wxStaticBitmap* gridImage = new wxStaticBitmap(parent, wxID_ANY, gridLines, wxPoint(0, 0), wxSize(400, 400));
}