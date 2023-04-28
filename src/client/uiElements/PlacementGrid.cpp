//
// Created by robin on 28.04.23.
//

#include "PlacementGrid.h"
#include <wx/wx.h>

PlacementGrid::PlacementGrid(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 400)) {
  wxColor backgroundColor = wxColor(255, 255, 0);
  this->SetBackgroundColour(backgroundColor);

  constexpr int gridSize = 10;

  //wxStaticBitmap* grid[10][10];
  this->_grid = new wxStaticBitmap*[gridSize*gridSize];

  wxBitmap emptyTile = wxBitmap(wxImage("../assets/empty_tile.png"));
  for (int i = 0; i < gridSize; i++) {
    for (int j = 0; j < gridSize; j++) {
      _grid[i*gridSize+j] = new wxStaticBitmap(parent, wxID_ANY, emptyTile, wxPoint(i*40, j*40), wxSize(40, 40));
    }
  }

  auto *gridLines = new wxBitmap(wxImage("../assets/grid_lines.png"));
  auto *gridImage = new wxStaticBitmap(parent, wxID_ANY, *gridLines, wxPoint(0, 0), wxSize(400, 400));
}