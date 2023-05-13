#include "SetupPanel.h"
#include "../SetupManager.h"
#include "../GameController.h"

// declare static variables
std::vector<Ship> SetupManager::_ships_placed;
Ship* SetupManager::_selectedShip;

/**
 * @brief Constructor of SetupPanel. Creates the panel and all its components.
 * @param parent
 */
SetupPanel::SetupPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS) {
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);

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

  // ----------------- event bindings -----------------
  _ship1->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent &evt) {
    SetupManager::_selectedShip = &SetupManager::_ships_placed[0];

    // display frame around ship button (static bitmap) to indicate selection
    /*
    wxPaintDC dc(_ship1);
    dc.SetPen(*wxGREEN_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(0, 0, _ship1->GetSize().GetWidth(), _ship1->GetSize().GetHeight());
    */

    if(SetupManager::_selectedShip->getPosition().x != -1 && SetupManager::_selectedShip->getPosition().y != -1) {
      std::cout << "this ship is already placed" << std::endl;
      _placementGrid->displayGrid();
      return;
    }
    std::cout << "ship 1 clicked (length: " << SetupManager::_selectedShip->getLength() << ", id: " << SetupManager::_selectedShip->getId().ToString() << ")" << std::endl;
  });

  _ship2->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent &evt) {
    SetupManager::_selectedShip = &SetupManager::_ships_placed[1];
    if(SetupManager::_selectedShip->getPosition().x != -1 && SetupManager::_selectedShip->getPosition().y != -1) {
      std::cout << "this ship is already placed" << std::endl;
      _placementGrid->displayGrid();
      return;
    }
    std::cout << "ship 2 clicked (length: " << SetupManager::_selectedShip->getLength() << ", id: " << SetupManager::_selectedShip->getId().ToString() << ")" << std::endl;
  });

  _ship3->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent &evt) {
    SetupManager::_selectedShip = &SetupManager::_ships_placed[2];
    if(SetupManager::_selectedShip->getPosition().x != -1 && SetupManager::_selectedShip->getPosition().y != -1) {
      std::cout << "this ship is already placed" << std::endl;
      _placementGrid->displayGrid();
      return;
    }
    std::cout << "ship 3 clicked (length: " << SetupManager::_selectedShip->getLength() << ", id: " << SetupManager::_selectedShip->getId().ToString() << ")" << std::endl;
  });

  _ship4->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent &evt) {
    SetupManager::_selectedShip = &SetupManager::_ships_placed[3];
    if(SetupManager::_selectedShip->getPosition().x != -1 && SetupManager::_selectedShip->getPosition().y != -1) {
      std::cout << "this ship is already placed" << std::endl;
      _placementGrid->displayGrid();
      return;
    }
    std::cout << "ship 4 clicked (length: " << SetupManager::_selectedShip->getLength() << ", id: " << SetupManager::_selectedShip->getId().ToString() << ")" << std::endl;
  });

  _ship5->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent &evt) {
    SetupManager::_selectedShip = &SetupManager::_ships_placed[4];
    if(SetupManager::_selectedShip->getPosition().x != -1 && SetupManager::_selectedShip->getPosition().y != -1) {
      std::cout << "this ship is already placed" << std::endl;
      _placementGrid->displayGrid();
      return;
    }
    std::cout << "ship 5 clicked (length: " << SetupManager::_selectedShip->getLength() << ", id: " << SetupManager::_selectedShip->getId().ToString() << ")" << std::endl;
  });
  // ----------------- end event bindings -----------------


  // add the vertical sizer to the right side of the horizontal sizer
  horizontalLayout->Add(verticalLayout, 0, wxEXPAND | wxALL, 20);

  // add the horizontal sizer to the main vertical sizer
  mainVerticalLayout->Add(horizontalLayout, 1, wxEXPAND | wxALL, 0);

  wxButton *readyButton = new wxButton(this, wxID_ANY, "Ready", wxDefaultPosition, wxSize(100, 40));
  mainVerticalLayout->Add(readyButton, 0, wxALIGN_RIGHT | wxTOP | wxBOTTOM, 10);
  readyButton->Bind(wxEVT_BUTTON, &SetupPanel::OnReadyButtonClicked, this);

  // Key event for rotating ship
  this->Bind(wxEVT_CHAR_HOOK, &SetupPanel::OnKeyDown, this);

  this->SetSizerAndFit(mainVerticalLayout);
}

/**
 * @brief Key Event handler for rotating ship. Rotates selected ship if 'R' is pressed.
 * @param event
 */
void SetupPanel::OnKeyDown(wxKeyEvent &event) {
  if (event.GetUnicodeKey() == 'R' || event.GetUnicodeKey() == 'r') {
    if (SetupManager::_selectedShip != nullptr && SetupManager::_selectedShip->getPosition().x == -1 &&
        SetupManager::_selectedShip->getPosition().y == -1) { // ship must not yet be placed
      std::cout << "rotate ship " << SetupManager::_selectedShip->getId().ToString() << std::endl;
      auto orientation = SetupManager::_selectedShip->getOrientation() == Ship::Orientation::Horizontal
                           ? Ship::Orientation::Vertical
                           : Ship::Orientation::Horizontal;
      SetupManager::_selectedShip->setOrientation(orientation);
      this->_placementGrid->highlightTiles(_placementGrid->cellX_prev, _placementGrid->cellY_prev); // re-highlight tiles
    }
  }
  event.Skip();
}


/**
 * @brief event handler for when the "Ready" button is clicked. Checks if all ships have been placed, and if so, notifies the GameController that the player is ready.
 * @param event wxCommandEvent
 */
void SetupPanel::OnReadyButtonClicked(wxCommandEvent &event) {
  if(SetupManager::placedAllShips()) {
    GameController::playerReady();
  }
  else {
    std::cout << "not all ships placed" << std::endl;
  }
}


/**
 * @brief helper function used in SetupManager::placeShip() to disable ship button after it has been placed
 * @param idx int in [0, 4] representing the index of the ship button to disable
 * @return wxStaticBitmap* representing the ship button that should be disabled. Returns NULL if idx is invalid.
 */
wxStaticBitmap *SetupPanel::getShipButton(int idx) {
  switch(idx) {
    case 0:
      return this->_ship1;
    case 1:
      return this->_ship2;
    case 2:
      return this->_ship3;
    case 3:
      return this->_ship4;
    case 4:
      return this->_ship5;
    default:
      return nullptr;
  }
}


/**
 * @brief getter for the placement grid
 * @return PlacementGrid* representing the placement grid
 */
PlacementGrid *SetupPanel::getPlacementGrid() const {
  return _placementGrid;
}
