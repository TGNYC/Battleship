#include "ViewGrid.h"

// #include <iostream>
#include "../common/Logger.h"
#include "../GameController.h"

ViewGrid::ViewGrid(wxWindow *parent, ViewGrid::gridtype type) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 400), wxWANTS_CHARS) {
    LOG("Constructing ViewGrid");
    _pos = this->GetPosition();
    _type = type;
    _parent = parent;
    wxColor backgroundColor = wxColor(255, 255, 0);
    this->SetBackgroundColour(backgroundColor);

    size_t x = _pos.x;
    size_t y = _pos.y;

    wxBoxSizer *gridTitle = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *gridTitleText;
    if (type == ViewGrid::gridtype::own) {
        gridTitleText = new wxStaticText(this, wxID_ANY, "Your grid [view grid]");
    } else {
        gridTitleText = new wxStaticText(this, wxID_ANY, "Opponent's grid [view grid]");
    }
    gridTitle->Add(gridTitleText, 0, wxALIGN_CENTER | wxALL, 0);

    constexpr int gridSize = 10;

    //wxStaticBitmap* grid[10][10];
    this->_grid = new wxStaticBitmap*[gridSize*gridSize];

    wxBitmap emptyTile = wxBitmap(wxImage("../assets/empty_tile.png"));
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            _grid[i*gridSize+j] = new wxStaticBitmap(this, wxID_ANY, emptyTile, wxPoint(x + i*40, y + j*40), wxSize(40, 40), 0);
        }
    }

    auto *gridLines = new wxBitmap(wxImage("../assets/grid_lines.png"));
    auto *gridImage = new wxStaticBitmap(this, wxID_ANY, *gridLines, wxPoint(x, y), wxSize(400, 400), 0);

    this->Bind(wxEVT_LEFT_DOWN, &ViewGrid::onMouseClick, this);
    this->Bind(wxEVT_MOTION, [this](wxMouseEvent &event) { // todo: delete, only for debugging
        this->SetFocus();
        LOG("Mouse moved");
    });

    this->SetFocus();
}

void ViewGrid::showShips(const std::vector<Ship>& ships) {
    for (auto ship : ships) {
        auto orientation = ship.getOrientation();
        int l = ship.getLength();
        Coordinate c = ship.getPosition();
        int x = c.x;
        int y = c.y;
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
            // std::cout << shots[i][j] << " ";
            if (shots[i][j] == 1) {
                int idx = i * 10 + j;
                _grid[idx]->SetBitmap(wxBitmap(wxImage("../assets/miss_tile.png")));
            } else if (shots[i][j] == 2) {
                int idx = i * 10 + j;
                _grid[idx]->SetBitmap(wxBitmap(wxImage("../assets/hit_tile.png")));
            }
        }
        // std::cout << std::endl;
    }
}

void ViewGrid::onMouseClick(wxMouseEvent &event) {
  this->SetFocus();
  if(_type == gridtype::own) {
        LOG("click on own grid is ignored");
        return;
  }
  LOG("clicked on opponent's grid");
  LOG("Mouse position: " + std::to_string(event.GetPosition().x) + ", " + std::to_string(event.GetPosition().y));

  // call GameController
  int cellX = event.GetPosition().x / 40;
  int cellY = event.GetPosition().y / 40;
  GameController::callShot(Coordinate(cellX, cellY));
}
