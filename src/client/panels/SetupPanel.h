#ifndef SETUPPANEL_H
#define SETUPPANEL_H

#include <wx/wx.h>
#include "../uiElements/PlacementGrid.h"

class SetupPanel : public wxPanel {
public:
  SetupPanel(wxWindow *parent);

private:
  PlacementGrid *_placementGrid;
  wxButton *_readyButton;
};

#endif // SETUPPANEL_H