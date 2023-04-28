#include "SetupPanel.h"

SetupPanel::SetupPanel(wxWindow *parent) : wxPanel(parent) {
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);

  wxBoxSizer *horizontalLayout = new wxBoxSizer(wxHORIZONTAL);

  this->_placementGrid = new PlacementGrid(this);
  horizontalLayout->Add(this->_placementGrid, 1, wxDEFAULT, 10);

  // TODO: add ship selection

  auto text = "Instructions:\n1. Select a ship\n2. Press R to rotate\n3. Click on the grid to place the ship\n4. Repeat until all ships are placed\n5. Click ready to start the game";
  wxStaticText* instructionText = new wxStaticText(this, wxID_ANY, text, wxPoint(400, 0), wxSize(200, 200), wxALIGN_BOTTOM);
  horizontalLayout->Add(instructionText, 0, wxDEFAULT, 10);

  this->_readyButton = new wxButton(this, wxID_ANY, "Ready", wxDefaultPosition, wxSize(100, 40));

  horizontalLayout->Add(this->_readyButton, 0, wxALIGN_BOTTOM, 10);
  this->SetSizerAndFit(horizontalLayout);
  //horizontalLayout->Layout();

}