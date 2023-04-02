#include "GameWindow.h"

#include <wx/wx.h>

GameWindow::GameWindow(const wxString &title, const wxPoint &pos,
                       const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size) {}