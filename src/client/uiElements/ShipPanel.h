#ifndef SHIPPANEL_H
#define SHIPPANEL_H

#include <wx/wx.h>
#include <string>
#include "../../common/game_state/Ship.h"

class ShipPanel : public wxPanel {
public:
    ShipPanel(wxWindow *parent, wxPoint pos, std::vector<Ship>& shipVector);
private:
    std::vector<Ship> _ships;
    wxStaticBitmap* _shipBitmaps[5];
};

#endif // SHIPPANEL_H