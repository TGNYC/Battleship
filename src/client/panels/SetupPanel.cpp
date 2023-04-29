#include "SetupPanel.h"

SetupPanel::SetupPanel(wxWindow *parent) : wxPanel(parent) {
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);
  /*
  wxBoxSizer *horizontalLayout = new wxBoxSizer(wxHORIZONTAL);

  this->_placementGrid = new PlacementGrid(this);
  horizontalLayout->Add(this->_placementGrid, 1, wxDEFAULT, 10);

  // TODO: add ship selection

  auto text = "Instructions:\n1. Select a ship\n2. Press R to rotate\n3. Click on the grid to place the ship\n4. Repeat until all ships are placed\n5. Click ready to start the game";
  wxBoxSizer *shipLayout = new wxBoxSizer(wxVERTICAL);
  wxStaticText* instructionText = new wxStaticText(this, wxID_ANY, text, wxPoint(400, 0), wxSize(200, 200), wxALIGN_BOTTOM);
  shipLayout->Add(instructionText, 0, wxDEFAULT, 10);

  this->_ship1 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/ship_tile.png")), wxDefaultPosition, wxSize(5*40, 40));
  this->_ship2 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/ship_tile.png")), wxDefaultPosition, wxSize(4*40, 40));
  this->_ship3 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/ship_tile.png")), wxDefaultPosition, wxSize(3*40, 40));
  this->_ship4 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/ship_tile.png")), wxDefaultPosition, wxSize(3*40, 40));
  this->_ship5 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/ship_tile.png")), wxDefaultPosition, wxSize(2*40, 40));
  // align ships below text vertically
  shipLayout->Add(this->_ship1, 0, wxALIGN_LEFT | wxTOP, 10);
  shipLayout->Add(this->_ship2, 0, wxALIGN_LEFT | wxTOP, 10);
  shipLayout->Add(this->_ship3, 0, wxALIGN_LEFT | wxTOP, 10);
  shipLayout->Add(this->_ship4, 0, wxALIGN_LEFT | wxTOP, 10);
  shipLayout->Add(this->_ship5, 0, wxALIGN_LEFT | wxTOP, 10);
  horizontalLayout->Add(shipLayout, 0, wxALIGN_BOTTOM | wxLEFT, 10);




  this->_readyButton = new wxButton(this, wxID_ANY, "Ready", wxDefaultPosition, wxSize(100, 40));

  horizontalLayout->Add(this->_readyButton, 0, wxALIGN_BOTTOM, 10);
  this->SetSizerAndFit(horizontalLayout);
  //horizontalLayout->Layout();
  */

  // create a main vertical sizer to contain the horizontal sizer and the ship images
  wxBoxSizer *mainVerticalLayout = new wxBoxSizer(wxVERTICAL);

  // create a horizontal sizer to contain the placement grid and instruction text
  wxBoxSizer *horizontalLayout = new wxBoxSizer(wxHORIZONTAL);

  // add the placement grid to the left side of the horizontal sizer
  this->_placementGrid = new PlacementGrid(this);
  horizontalLayout->Add(this->_placementGrid, 1, wxDEFAULT, 0);

  // create a vertical sizer to contain the instruction text and ship images
  wxBoxSizer *verticalLayout = new wxBoxSizer(wxVERTICAL);

  // add the instruction text to the top of the vertical sizer
  auto text = "Instructions:\n1. Select a ship\n2. Press R to rotate\n3. Click on the grid to place the ship\n4. Repeat until all ships are placed\n5. Click ready to start the game";
  wxStaticText* instructionText = new wxStaticText(this, wxID_ANY, text);
  verticalLayout->Add(instructionText, 0, wxALIGN_TOP | wxALL, 10);

  // add the ship images to the bottom of the vertical sizer
  this->_ship1 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/ship_1.png")), wxDefaultPosition, wxSize(5*40, 40));
  this->_ship2 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/ship_2.png")), wxDefaultPosition, wxSize(4*40, 40));
  this->_ship3 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/ship_3.png")), wxDefaultPosition, wxSize(3*40, 40));
  this->_ship4 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/ship_4.png")), wxDefaultPosition, wxSize(3*40, 40));
  this->_ship5 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/ship_5.png")), wxDefaultPosition, wxSize(2*40, 40));
  verticalLayout->Add(this->_ship1, 0, wxALIGN_LEFT | wxBOTTOM, 10);
  verticalLayout->Add(this->_ship2, 0, wxALIGN_LEFT | wxBOTTOM, 10);
  verticalLayout->Add(this->_ship3, 0, wxALIGN_LEFT | wxBOTTOM, 10);
  verticalLayout->Add(this->_ship4, 0, wxALIGN_LEFT | wxBOTTOM, 10);
  verticalLayout->Add(this->_ship5, 0, wxALIGN_LEFT | wxBOTTOM, 10);

  // add the vertical sizer to the right side of the horizontal sizer
  horizontalLayout->Add(verticalLayout, 0, wxEXPAND | wxALL, 20);

  // add the horizontal sizer to the main vertical sizer
  mainVerticalLayout->Add(horizontalLayout, 1, wxEXPAND | wxALL, 0);

  // add the "Ready" button to the bottom of the main vertical sizer
  this->_readyButton = new wxButton(this, wxID_ANY, "Ready", wxDefaultPosition, wxSize(100, 40));

  mainVerticalLayout->Add(this->_readyButton, 0, wxALIGN_RIGHT | wxTOP | wxBOTTOM, 10);

  this->SetSizerAndFit(mainVerticalLayout);
        //horizontalLayout->Layout();
        //this->Layout();
}