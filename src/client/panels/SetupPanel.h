#ifndef SETUPPANEL_H
#define SETUPPANEL_H

#include "../SetupManager.h"
#include "../uiElements/PlacementGrid.h"
#include <wx/wx.h>

class SetupPanel : public wxPanel {
public:
  /**
   * @brief Constructor of SetupPanel. Creates the panel and all its components.
   * @param parent
   */
  SetupPanel(wxWindow *parent);

  /**
   * @brief event handler for when the "Ready" button is clicked. Checks if all ships have been placed, and if so,
   * notifies the GameController that the player is ready.
   * @param event wxCommandEvent
   */
  void OnReadyButtonClicked(wxCommandEvent &event);

  /**
   * @brief Key Event handler for rotating ship. Rotates selected ship if 'R' is pressed.
   * @param event
   */
  void OnKeyDown(wxKeyEvent &event);

  /**
   * @brief helper function used in SetupManager::placeShip() to disable ship button after it has been placed
   * @param idx int in [0, 4] representing the index of the ship button to disable
   * @return wxStaticBitmap* representing the ship button that should be disabled. Returns NULL if idx is invalid.
   */
  wxStaticBitmap *getShipButton(int idx);

  /**
   * @brief getter for the ready button (for GameController to disable after it has been clicked)
   * @return wxButton* pointing to the ready button
   */
  wxButton *getReadyButton() const;

  wxStaticText *getReadyText() const;

private:
  PlacementGrid                *_placementGrid;
  wxStaticBitmap               *_ship1;
  wxStaticBitmap               *_ship2;
  wxStaticBitmap               *_ship3;
  wxStaticBitmap               *_ship4;
  wxStaticBitmap               *_ship5;
  wxStaticBitmap               *_selectedBitmap;
  std::vector<wxStaticBitmap *> _ships;

  wxButton     *_readyButton;
  wxStaticText *_readyText;
};

#endif // SETUPPANEL_H