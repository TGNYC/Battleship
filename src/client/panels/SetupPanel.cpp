#include "SetupPanel.h"

SetupPanel::SetupPanel(wxWindow *parent) : wxPanel(parent) {
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->setBackgroundColor(backgroundColor);

  wxBoxSizer *verticalLayout = new wxBoxSizer(wxVERTICAL);

  // TODO: add ship placement grid

  // TODO: add ship selection 

  this->_readyButton = new wxButton(this, wxID_ANY, "Ready", wxDefaultPosition, wxSize(100, 40));
}