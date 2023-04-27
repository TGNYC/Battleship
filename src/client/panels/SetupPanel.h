#ifndef SETUPPANEL_H
#define SETUPPANEL_H

#include <wx/wx.h>

class SetupPanel : public wxPanel {
public:
  SetupPanel(wxWindow *parent);

private:
  wxButton *_readyButton;
};

#endif // SETUPPANEL_H