#include "ShipPanel.h"
#include <iostream>

ShipPanel::ShipPanel(wxWindow *parent, wxPoint pos, const std::array<bool, 5> sunk)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 100)) {
  // set the minimum size of the panel to 400x100
  this->SetMinSize(wxSize(400, 100));

  std::string filenames[5] = {"../assets/ship_1.png", "../assets/ship_2.png", "../assets/ship_3.png",
                              "../assets/ship_4.png", "../assets/ship_5.png"};

  std::string filenamesSunk[5] = {"../assets/ship_1_sunk.png", "../assets/ship_2_sunk.png", "../assets/ship_3_sunk.png",
                                  "../assets/ship_4_sunk.png", "../assets/ship_5_sunk.png"};

  int positions[5][2] = {{pos.x + 0 * 40, pos.y + 0 * 30},
                         {pos.x + 6 * 40, pos.y + 0 * 30},
                         {pos.x + 0 * 40, pos.y + 2 * 30},
                         {pos.x + 4 * 40, pos.y + 2 * 30},
                         {pos.x + 8 * 40, pos.y + 2 * 30}};

  int lengths[5] = {5, 4, 3, 3, 2};

  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);

  for (size_t i = 0; i < 5; ++i) {
    // std::cout << positions[i][0] << " " << positions[i][1] << " " << filenames[i] << " " << ships[i].getLength() <<
    // std::endl;
    if (sunk[i]) {
      this->_shipBitmaps[i] =
          new wxStaticBitmap(parent, wxID_ANY, wxBitmap(wxImage(filenamesSunk[i])),
                             wxPoint(positions[i][0], positions[i][1]), wxSize(lengths[i] * 40, 40));
    } else {
      this->_shipBitmaps[i] =
          new wxStaticBitmap(parent, wxID_ANY, wxBitmap(wxImage(filenames[i])),
                             wxPoint(positions[i][0], positions[i][1]), wxSize(lengths[i] * 40, 40));
    }
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

