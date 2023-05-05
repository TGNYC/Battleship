//
// Created by robin on 28.04.23.
//

#include "PlacementGrid.h"
#include <wx/wx.h>
#include "../SetupManager.h"


PlacementGrid::PlacementGrid(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 400)) {
  wxColor backgroundColor = wxColor(255, 255, 0);
  this->SetBackgroundColour(backgroundColor);

  constexpr int gridSize = 10;

  //wxStaticBitmap* grid[10][10];
  this->_grid = new wxStaticBitmap*[gridSize*gridSize];

  wxBitmap emptyTile = wxBitmap(wxImage("../assets/empty_tile.png"));
  for (int i = 0; i < gridSize; i++) {
    for (int j = 0; j < gridSize; j++) {
      _grid[i*gridSize+j] = new wxStaticBitmap(parent, wxID_ANY, emptyTile, wxPoint(i*40, j*40), wxSize(40, 40), 0);
    }
  }

  auto *gridLines = new wxBitmap(wxImage("../assets/grid_lines.png"));
  auto *gridImage = new wxStaticBitmap(parent, wxID_ANY, *gridLines, wxPoint(0, 0), wxSize(400, 400));

  Bind(wxEVT_MOTION, &PlacementGrid::OnMouseMotion, this);
  Bind(wxEVT_LEFT_DOWN, &PlacementGrid::OnMouseClick, this);
}

void PlacementGrid::OnMouseMotion(wxMouseEvent &event) {
  wxPoint mousePosition = event.GetPosition();
  int CellX = mousePosition.x / 40;
  int CellY = mousePosition.y / 40;
  //std::cout << "(" << CellX << ", " << CellY << ")\n";

  if(CellX == cellX_prev && CellY == cellY_prev) { // same as before
    return;
  }
  if(CellX < 0 || CellX >= 10 || CellY < 0 || CellY >= 10 || SetupManager::_selectedShip == nullptr) { // out of bounds or no ship selected
    return;
  }

  // grid is column major!

  int l = SetupManager::_selectedShip->getLength();
  auto orientation = SetupManager::_selectedShip->getOrientation();
  //orientation = Ship::Orientation::Vertical;
  // clear previous highlighted tiles
  if(cellX_prev != -1 && cellY_prev != -1) {
    if(orientation == Ship::Orientation::Horizontal) {
      for(int i = 0; i < l; i++) {
        int idx = (cellX_prev+i)*10+cellY_prev;
        if(cellX_prev + i < 10 && cellY_prev < 10)
          _grid[idx]->SetBitmap(wxBitmap(wxImage("../assets/empty_tile.png")));
      }
    }
    else if(orientation == Ship::Orientation::Vertical) {
      for(int i = 0; i < l; i++) {
        int idx = cellX_prev*10+cellY_prev+i;
        if(cellX_prev < 10 && cellY_prev + i < 10)
          _grid[idx]->SetBitmap(wxBitmap(wxImage("../assets/empty_tile.png")));
      }
    }
  }

  // highlight new tiles
  if (orientation == Ship::Orientation::Horizontal) {
    for (int i = 0; i < l; i++) {
      int idx = (CellX + i) * 10 + CellY;
      if (CellX + i < 10 && CellY < 10)
        _grid[idx]->SetBitmap(wxBitmap(wxImage("../assets/ship_tile.png")));
    }
  } else if (orientation == Ship::Orientation::Vertical) {
    for (int i = 0; i < l; i++) {
      int idx = CellX * 10 + CellY + i;
      if (CellX < 10 && CellY + i < 10)
        _grid[idx]->SetBitmap(wxBitmap(wxImage("../assets/ship_tile.png")));
    }
  }

  cellX_prev = CellX;
  cellY_prev = CellY;

  this->displayGrid();

  //this->_grid[CellX*10+CellY]->SetBitmap(wxBitmap(wxImage("../assets/ship_tile.png")));

}
void PlacementGrid::OnMouseClick(wxMouseEvent &event) {
  if(SetupManager::_selectedShip == nullptr) {
    std::cout << "no ship selected" << std::endl;
    return;
  }
  if(SetupManager::_selectedShip->getPosition().x != -1 && SetupManager::_selectedShip->getPosition().y != -1) {
    std::cout << "this ship is already placed" << std::endl;
    return;
  }

  wxPoint mousePosition = event.GetPosition();
  std::cout << "clicked at (" << mousePosition.x/40 << ", " << mousePosition.y/40 << ")\n";
  auto *grid = SetupManager::getGrid();
  if (!SetupManager::placeShip(mousePosition, SetupManager::_selectedShip)) return;
  std::cout << "placed ship\n";

  this->displayGrid();


}
void PlacementGrid::displayGrid() {
  auto *grid = SetupManager::getGrid();
  for(int i = 0; i < 100; ++i) {
    if(grid[i] != 0) {
      _grid[i]->SetBitmap(wxBitmap(wxImage("../assets/ship_tile.png")));
    }
  }
}
