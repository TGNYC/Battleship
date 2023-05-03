#include "ViewGrid.h"

ViewGrid::ViewGrid(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 400)) {
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
}

void ViewGrid::placeShips(std::vector<Ship> ships) {
    for (auto ship : ships) {
        auto orientation = ship.getOrientation();
        int l = ship.getLength();
        int x = ship.getX();
        int y = ship.getY();
        if (orientation == Ship::Orientation::Horizontal) {
            for (int i = 0; i < l; i++) {
                int idx = (x + i) * 10 + y;
                if (x + i < 10 && y < 10)
                _grid[idx]->SetBitmap(wxBitmap(wxImage("../assets/ship_tile.png")));
            }
        } else if (orientation == Ship::Orientation::Vertical) {
            for (int i = 0; i < l; i++) {
                int idx = x * 10 + y + i;
                if (x < 10 && y + i < 10)
                _grid[idx]->SetBitmap(wxBitmap(wxImage("../assets/ship_tile.png")));
            }
        }
    }
}