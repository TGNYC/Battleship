#ifndef SETUPPANEL_H
#define SETUPPANEL_H

#include <wx/wx.h>
#include "../uiElements/PlacementGrid.h"
#include "../SetupManager.h"

class SetupPanel : public wxPanel {
public:
  SetupPanel(wxWindow *parent);

  PlacementGrid* getPlacementGrid() const {
    return _placementGrid;
  }


private:
  PlacementGrid *_placementGrid;
  wxButton *_readyButton;
  wxStaticBitmap *_ship1;
  wxStaticBitmap *_ship2;
  wxStaticBitmap *_ship3;
  wxStaticBitmap *_ship4;
  wxStaticBitmap *_ship5;

};

#endif // SETUPPANEL_H