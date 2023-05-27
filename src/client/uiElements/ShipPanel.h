#ifndef SHIPPANEL_H
#define SHIPPANEL_H

#include "game_state/Ship.h"
#include <string>
#include <wx/wx.h>

class ShipPanel : public wxPanel {
public:
  ShipPanel(wxWindow *parent, wxPoint pos, const std::array<bool, 5> sunk);

  /**
   * @brief Updates the panel to show the ships that have been sunk.
   * @param sunk An array of booleans, where true means that the ship has been sunk.
   * The ships are sorted by length, the ship at index 0 is the longest one with length 5.
  */
  void update(const std::array<bool, 5> sunk);

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