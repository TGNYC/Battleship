#include "ViewGrid.h"
#include "Logger.h"

ViewGrid::ViewGrid(wxWindow *parent, ViewGrid::GridType type)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 400), wxWANTS_CHARS) {
  LOG("constructing ViewGrid");
  _pos                    = this->GetPosition();
  _type                   = type;
  _parent                 = parent;
  wxColor backgroundColor = wxColor(255, 255, 0);
  this->SetBackgroundColour(backgroundColor);

  const int x = _pos.x;
  const int y = _pos.y;

  constexpr int gridSize = 10;

  this->_grid = new wxStaticBitmap *[gridSize * gridSize];

  wxBitmap emptyTile = wxBitmap(wxImage("../assets/empty_tile.png"));
  for (int i = 0; i < gridSize; i++) {
    for (int j = 0; j < gridSize; j++) {
      _grid[i * gridSize + j] =
          new wxStaticBitmap(this, wxID_ANY, emptyTile, wxPoint(x + i * 40, y + j * 40), wxSize(40, 40), 0);
      _grid[i * gridSize + j]->Bind(wxEVT_LEFT_DOWN, [this, i, j](wxMouseEvent &event) {
        if (_type == GridType::own)
          return;
        LOG("clicked on tile " + std::to_string(i) + ", " + std::to_string(j));
        GameController::callShot(Coordinate{i, j});
      });
    }
  }

  auto *gridLines = new wxBitmap(wxImage("../assets/grid_lines.png"));
  auto *gridImage = new wxStaticBitmap(this, wxID_ANY, *gridLines, wxPoint(x, y), wxSize(400, 400), 0);

  this->SetFocus();
}

void ViewGrid::showShips(const std::vector<Ship> &ships) {
  for (auto ship : ships) {
    auto       orientation = ship.getOrientation();
    int        l           = ship.getLength();
    Coordinate c           = ship.getPosition();
    int        x           = c.x;
    int        y           = c.y;
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

void ViewGrid::showShots(const int shots[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (shots[i][j] == 1) {
        int idx = i * 10 + j;
        _grid[idx]->SetBitmap(wxBitmap(wxImage("../assets/miss_tile.png")));
      } else if (shots[i][j] == 2) {
        int idx = i * 10 + j;
        _grid[idx]->SetBitmap(wxBitmap(wxImage("../assets/hit_tile.png")));
      }
    }
  }
}
