#include "SetupPanel.h"

SetupPanel::SetupPanel(wxWindow *parent) : wxPanel(parent) {
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);

  wxBoxSizer *horizontalLayout = new wxBoxSizer(wxHORIZONTAL);

  this->_placementGrid = new PlacementGrid(this);
  horizontalLayout->Add(this->_placementGrid, 1, wxDEFAULT, 10);

  // TODO: add ship selection

  this->_readyButton = new wxButton(this, wxID_ANY, "Ready", wxDefaultPosition, wxSize(100, 40));

  horizontalLayout->Add(this->_readyButton, 0, wxALIGN_BOTTOM, 10);
  this->SetSizerAndFit(horizontalLayout);
  //horizontalLayout->Layout();

}