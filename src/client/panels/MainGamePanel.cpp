#include "MainGamePanel.h"

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(960, 680)) {
  // static text: hello world
  auto *helloWorld = new wxStaticText(this, wxID_ANY, "Hello World!", wxPoint(10, 10), wxSize(100, 20), 0);


}