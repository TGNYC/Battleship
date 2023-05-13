#ifndef SETUPPANEL_H
#define SETUPPANEL_H

#include <wx/wx.h>
#include "../uiElements/PlacementGrid.h"
#include "../SetupManager.h"

class SetupPanel : public wxPanel {
public:
  SetupPanel(wxWindow *parent);
  void OnReadyButtonClicked(wxCommandEvent &event);
  void OnKeyDown(wxKeyEvent &event);

  PlacementGrid* getPlacementGrid() const;

  wxStaticBitmap* getShipButton(int idx);

private:
  PlacementGrid *_placementGrid;
  wxStaticBitmap *_ship1;
  wxStaticBitmap *_ship2;
  wxStaticBitmap *_ship3;
  wxStaticBitmap *_ship4;
  wxStaticBitmap *_ship5;
  wxStaticBitmap *_selectedBitmap;
  std::vector<wxStaticBitmap*> _ships;
};

#endif // SETUPPANEL_H