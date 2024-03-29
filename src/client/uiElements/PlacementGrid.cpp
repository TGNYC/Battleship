//
// Created by robin on 28.04.23.
//

#include "PlacementGrid.h"
#include "../SetupManager.h"
#include "Logger.h"
#include <wx/wx.h>

PlacementGrid::PlacementGrid(wxWindow *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 400), wxWANTS_CHARS) {
  wxColor backgroundColor = wxColor(255, 255, 0); // yellow, for debugging, shouldn't be visible
  this->SetBackgroundColour(backgroundColor);

  constexpr int gridSize = 10;
  this->_grid            = new wxStaticBitmap *[gridSize * gridSize];

  wxBitmap emptyTile = wxBitmap(wxImage("../assets/empty_tile.png"));
  for (int i = 0; i < gridSize; i++) {
    for (int j = 0; j < gridSize; j++) {
      _grid[i * gridSize + j] =
          new wxStaticBitmap(parent, wxID_ANY, emptyTile, wxPoint(10 + i * 40, 10 + j * 40), wxSize(40, 40), 0);
    }
  }

  auto                  *gridLines = new wxBitmap(wxImage("../assets/grid_lines.png"));
  [[maybe_unused]] auto *gridImage =
      new wxStaticBitmap(parent, wxID_ANY, *gridLines, wxPoint(10, 10), wxSize(400, 400));

  Bind(wxEVT_MOTION, &PlacementGrid::OnMouseMotion, this);
  Bind(wxEVT_LEFT_DOWN, &PlacementGrid::OnMouseClick, this);
}

void PlacementGrid::OnMouseMotion(wxMouseEvent &event) {
  this->SetFocus(); // set focus such that key events are received (for rotation)
  wxPoint mousePosition = event.GetPosition();
  int     CellX         = mousePosition.x / 40;
  int     CellY         = mousePosition.y / 40;

  highlightTiles(CellX, CellY);
}

void PlacementGrid::OnMouseClick(wxMouseEvent &event) {
  if (SetupManager::_selectedShip == nullptr) {
    LOG("no ship selected");
    return;
  }
  if (SetupManager::_selectedShip->getPosition().x != -1 && SetupManager::_selectedShip->getPosition().y != -1) {
    LOG("this ship is already placed");
    return;
  }

  wxPoint mousePosition = event.GetPosition();
  LOG("clicked at (" + std::to_string(mousePosition.x / 40) + ", " + std::to_string(mousePosition.y / 40) + ")");
  if (!SetupManager::placeShip(mousePosition, SetupManager::_selectedShip))
    return;
  LOG("placed ship");

  this->displayGrid();
}

void PlacementGrid::displayGrid() {
  auto *grid = SetupManager::getGrid();
  for (int i = 0; i < 100; ++i) {
    if (grid[i] != 0) {
      _grid[i]->SetBitmap(wxBitmap(wxImage("../assets/ship_tile.png")));
    } else {
      _grid[i]->SetBitmap(wxBitmap(wxImage("../assets/empty_tile.png")));
    }
  }
}

void PlacementGrid::highlightTiles(int CellX, int CellY) {
  if (SetupManager::_selectedShip == nullptr) { // no ship selected
    return;
  }
  if (SetupManager::_selectedShip->getPosition().x != -1 &&
      SetupManager::_selectedShip->getPosition().y != -1) { // already placed
    return;
  }
  if (SetupManager::_selectedShip->getOrientation() == Ship::Orientation::Horizontal &&
      CellX + SetupManager::_selectedShip->getLength() > 10) { // ship would be out of bounds
    CellX = std::min(CellX, 10 - SetupManager::_selectedShip->getLength());
  }
  if (SetupManager::_selectedShip->getOrientation() == Ship::Orientation::Vertical &&
      CellY + SetupManager::_selectedShip->getLength() > 10) { // ship would be out of bounds
    CellY = std::min(CellY, 10 - SetupManager::_selectedShip->getLength());
  }

  this->displayGrid();

  const int l           = SetupManager::_selectedShip->getLength();
  auto      orientation = SetupManager::_selectedShip->getOrientation();

  // highlight new tiles
  if (orientation == Ship::Orientation::Horizontal) {
    for (int i = 0; i < l; i++) {
      int idx = (CellX + i) * 10 + CellY; // column-major order
      if (idx < 0 || idx > 99)
        continue;
      if (CellX + i < 10 && CellY < 10)
        _grid[idx]->SetBitmap(wxBitmap(wxImage("../assets/ship_tile.png")));
    }
  } else if (orientation == Ship::Orientation::Vertical) {
    for (int i = 0; i < l; i++) {
      int idx = CellX * 10 + CellY + i;
      if (idx < 0 || idx > 99)
        continue;
      if (CellX < 10 && CellY + i < 10)
        _grid[idx]->SetBitmap(wxBitmap(wxImage("../assets/ship_tile.png")));
    }
  }

  cellX_prev = CellX;
  cellY_prev = CellY;
}
