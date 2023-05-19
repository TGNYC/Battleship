#ifndef SHIPPANEL_H
#define SHIPPANEL_H

#include <wx/wx.h>
#include <string>
#include "../../common/game_state/Ship.h"

class ShipPanel : public wxPanel {
public:
    ShipPanel(wxWindow *parent, wxPoint pos, const bool sunk[5]);
private:
    wxStaticBitmap* _shipBitmaps[5];
    std::string _filenames[5] = {
        "../assets/ship_1.png",
        "../assets/ship_2.png",
        "../assets/ship_3.png",
        "../assets/ship_4.png",
        "../assets/ship_5.png"
    };

    std::string _filenamesSunk[5] = {
        "../assets/ship_1_sunk.png",
        "../assets/ship_2_sunk.png",
        "../assets/ship_3_sunk.png",
        "../assets/ship_4_sunk.png",
        "../assets/ship_5_sunk.png"
    };
};

#endif // SHIPPANEL_H