#ifndef SHIPPANEL_H
#define SHIPPANEL_H

#include "game_state/Ship.h"
#include <string>
#include <wx/wx.h>

class ShipPanel : public wxPanel {
public:
  ShipPanel(wxWindow *parent, wxPoint pos, const std::array<bool, 5> sunk);

private:
  wxStaticBitmap *_shipBitmaps[5];
};

#endif // SHIPPANEL_H