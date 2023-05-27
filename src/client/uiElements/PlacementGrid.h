//
// Created by robin on 28.04.23.
//

#ifndef BATTLESHIP_PLACEMENTGRID_H
#define BATTLESHIP_PLACEMENTGRID_H

#include <wx/wx.h>

class PlacementGrid : public wxPanel {
public:
  /**
  * @brief constructor for PlacementGrid. Creates grid of 10x10 tiles and binds mouse events
  * @param parent
  */
  PlacementGrid(wxWindow *parent);

  /**
  * @brief function is called when mouse hovers over grid and highlights tiles according to mouse position and placed ships
  * @param event mouse event
  */
  void OnMouseMotion(wxMouseEvent &event);

  /**
  * @brief function is called when mouse clicks on grid and places ship if possible
  * @param event
  */
  void OnMouseClick(wxMouseEvent &event);

  /**
  * @brief function displays grid according to data in SetupManager
  */
  void displayGrid();

  /**
  * @brief function highlights tiles according to mouse position and placed ships
  * @param CellX x coordinate of mouse position
  * @param CellY y coordinate of mouse position
  */
  void highlightTiles(int CellX, int CellY);

  int cellX_prev = -1;
  int cellY_prev = -1;

private:
  wxStaticBitmap **_grid;
};

#endif // BATTLESHIP_PLACEMENTGRID_H
