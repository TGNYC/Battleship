#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <wx/wx.h>

class GameWindow : public wxFrame {
public:
  GameWindow(const wxString &title, const wxPoint &pos, const wxSize &size);
  void showPanel(wxPanel *panel);
  void setStatus(const std::string &message);
  void onClose(wxCloseEvent &event);

private:
  wxBoxSizer  *_mainLayout;
  wxStatusBar *_statusBar;
  wxPanel     *_currentPanel;
};

#endif // GAMEWINDOW_H