#include "ShipPanel.h"
#include <iostream>

ShipPanel::ShipPanel(wxWindow *parent, wxPoint pos, std::vector<Ship>& ships) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 120)) {
    _ships = ships;
    std::string filenames[5] = {
        "../assets/ship_1.png",
        "../assets/ship_2.png",
        "../assets/ship_3.png",
        "../assets/ship_4.png",
        "../assets/ship_5.png"
    };

    std::string filenamesSunk[5] = {
        "../assets/ship_1_sunk.png",
        "../assets/ship_2_sunk.png",
        "../assets/ship_3_sunk.png",
        "../assets/ship_4_sunk.png",
        "../assets/ship_5_sunk.png"
    };

    size_t positions[5][2] = {
        {pos.x + 0*40, pos.y + 0*30},
        {pos.x + 6*40, pos.y + 0*30},
        {pos.x + 0*40, pos.y + 2*30},
        {pos.x + 4*40, pos.y + 2*30},
        {pos.x + 8*40, pos.y + 2*30}
    };

    wxColor backgroundColor = wxColor(255, 255, 255);
    this->SetBackgroundColour(backgroundColor);

    for (size_t i=0; i<_ships.size(); ++i) {
        // std::cout << positions[i][0] << " " << positions[i][1] << " " << filenames[i] << " " << ships[i].getLength() << std::endl;
        if (_ships[i].hasSunken()) {
            this->_shipBitmaps[i] = new wxStaticBitmap(parent, wxID_ANY, wxBitmap(wxImage(filenamesSunk[i])), wxPoint(positions[i][0], positions[i][1]), wxSize(ships[i].getLength()*40, 40));
        } else {
            this->_shipBitmaps[i] = new wxStaticBitmap(parent, wxID_ANY, wxBitmap(wxImage(filenames[i])), wxPoint(positions[i][0], positions[i][1]), wxSize(ships[i].getLength()*40, 40));
        }
    }

    // for (size_t i=0; i<ships.size(); i++) {
        // Ship ship = ships[i];
        // auto orientation = ship.getOrientation();
        // int l = ship.getLength();
        // Coordinate c = ship.getPosition();
        // int x = c.x;
        // int y = c.y;
        // if (orientation == Ship::Orientation::Horizontal) {
        //     for (int i = 0; i < l; i++) {
        //         _shipImages.push_back(new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/ship_tile.png")), wxPoint(pos.x + x*40 + i*40, pos.y + y*40), wxSize(40, 40), 0));
        //     }
        // } else if (orientation == Ship::Orientation::Vertical) {
        //     for (int i = 0; i < l; i++) {
        //         _shipImages.push_back(new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/ship_tile.png")), wxPoint(pos.x + x*40, pos.y + y*40 + i*40), wxSize(40, 40), 0));
        //     }
        // }
    // }
}