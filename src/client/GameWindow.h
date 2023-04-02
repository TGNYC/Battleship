#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <wx/wx.h>

class GameWindow : public wxFrame {
public:
  GameWindow(const wxString &title, const wxPoint &pos, const wxSize &size);
};

#endif // GAMEWINDOW_H