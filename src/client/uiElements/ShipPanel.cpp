#include "ShipPanel.h"
#include <iostream>

ShipPanel::ShipPanel(wxWindow *parent, wxPoint pos, std::array<bool, 5> sunk) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 100)) {
  // set the minimum size of the panel to 400x100
  this->SetMinSize(wxSize(400, 100));

  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);

  //wxGridSizer* gridSizer = new wxGridSizer(2, 3, 5, 5);
  int positions[5][2] = {
      {pos.x + 0*40, pos.y + 0*30},
      {pos.x + 6*40, pos.y + 0*30},
      {pos.x + 0*40, pos.y + 2*30},
      {pos.x + 4*40, pos.y + 2*30},
      {pos.x + 8*40, pos.y + 2*30}
  };

  int lengths[5] = {5, 4, 3, 3, 2};

  for (size_t i=0; i<5; ++i) {
    _shipBitmaps[i] = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage(_filenames[i])), wxPoint(positions[i][0], positions[i][1]), wxSize(lengths[i]*40, 40));
  }
}


void ShipPanel::update(const std::array<bool, 5> sunk) {
  for (size_t i=0; i<5; ++i) {
    if (sunk[i]) {
      _shipBitmaps[i]->SetBitmap(wxBitmap(wxImage(_filenamesSunk[i])));
    }
    else {
      _shipBitmaps[i]->SetBitmap(wxBitmap(wxImage(_filenames[i])));
    }
  }
}

