#ifndef VIEWGRID_H
#define VIEWGRID_H

#include "../../common/game_state/Ship.h"
#include <wx/wx.h>

class ViewGrid : public wxPanel {
public:
  enum GridType {
    own,
    opp
  };

  ViewGrid(wxWindow *parent, GridType type);

  /**
   * @brief Displays the ships on the grid.
   * @param ships A vector of ships that will be displayed.
   * Displays the ships on the grid using the ship's position and orientation.
   * This function should only be called for the own grid.
   */
  void showShips(const std::vector<Ship> &ships);

  /**
   * @brief Displays the shots on the grid.
   * @param shots A 2D array of integers, where 0 means no shot, 1 means a miss and 2 means a hit.
   * A miss is marked with a white dot and a hit is marked with a red dot.
   */
  void showShots(const int shots[10][10]);

private:
  wxPoint          _pos;
  wxStaticBitmap **_grid;
  GridType         _type;
  wxWindow        *_parent;
};

#endif // VIEWGRID_H