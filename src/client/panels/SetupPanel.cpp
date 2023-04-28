#include "SetupPanel.h"

SetupPanel::SetupPanel(wxWindow *parent) : wxPanel(parent) {
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);

  wxBoxSizer *verticalLayout = new wxBoxSizer(wxVERTICAL);

  this->_placementGrid = new PlacementGrid(this);
  verticalLayout->Add(this->_placementGrid, 1, wxDEFAULT, 10);

  // TODO: add ship selection

  this->_readyButton = new wxButton(this, wxID_ANY, "Ready", wxDefaultPosition, wxSize(100, 40));

  verticalLayout->Add(this->_readyButton, 0, wxALIGN_CENTER, 10);
  this->SetSizerAndFit(verticalLayout);
  //verticalLayout->Layout();

}