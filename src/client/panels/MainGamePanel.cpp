#include "MainGamePanel.h"
#include "Logger.h"

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
  LOG("Constructing MainGamePanel");
  parent->SetMinSize(wxSize(1200, 800));
  // For some reason, the ShipPanels take up way too much space after this->SetSizer(_mainWindow) on line 61 is called.
  // Before, they have a size of 400x100, afterwards it's 400x400.
  // This limits the maximum size of the window, but it's not a good fix.
  parent->SetMaxSize(wxSize(1200, 800));

  _mainWindow               = new wxBoxSizer(wxHORIZONTAL);
  _emoteWindow              = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *gameWindow    = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *turnIndicator = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *grids         = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *leftSide      = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *rightSide     = new wxBoxSizer(wxVERTICAL);

  std::array<bool, 5> init = {false, false, false, false, false};
  this->_ownShipPanel      = new ShipPanel(this, wxDefaultPosition, init);
  this->_oppShipPanel      = new ShipPanel(this, wxDefaultPosition, init);

  this->_ownViewGrid = new ViewGrid(this, ViewGrid::GridType::own);
  this->_oppViewGrid = new ViewGrid(this, ViewGrid::GridType::opp);

  wxBoxSizer   *leftTitleSizer = new wxBoxSizer(wxVERTICAL);
  wxStaticText *leftTitle      = new wxStaticText(this, wxID_ANY, "Your Ships");
  leftTitleSizer->Add(leftTitle, 1, wxALIGN_CENTER_HORIZONTAL);
  leftSide->Add(leftTitleSizer, 0, wxEXPAND | wxTOP, 10);
  leftSide->Add(_ownViewGrid, 1, wxEXPAND | wxALL, 10);
  leftSide->Add(_ownShipPanel, 1, wxEXPAND | wxALL, 10);

  wxBoxSizer   *rightTitleSizer = new wxBoxSizer(wxVERTICAL);
  wxStaticText *rightTitle      = new wxStaticText(this, wxID_ANY, "Opponent's Ships");
  rightTitleSizer->Add(rightTitle, 1, wxALIGN_CENTER_HORIZONTAL);
  rightSide->Add(rightTitleSizer, 0, wxEXPAND | wxTOP, 10);
  rightSide->Add(_oppViewGrid, 1, wxEXPAND | wxALL, 10);
  rightSide->Add(_oppShipPanel, 1, wxEXPAND | wxALL, 10);

  grids->Add(leftSide, 1, wxEXPAND | wxALL, 10);
  grids->Add(rightSide, 1, wxEXPAND | wxALL, 10);

  _turnText = new wxStaticText(this, wxID_ANY, "[TURN INDICATOR]");
  turnIndicator->Add(_turnText, 0, wxALIGN_CENTER_HORIZONTAL, 0);

  gameWindow->Add(turnIndicator, 0, wxEXPAND | wxTOP, 10);
  gameWindow->Add(grids, 1, wxEXPAND | wxLEFT | wxBOTTOM | wxRIGHT, 10);

  _emotePanel = new EmotePanel(this, wxDefaultPosition);
  _emoteWindow->Add(_emotePanel, 1, wxEXPAND | wxALL, 10);

  _mainWindow->Add(_emoteWindow, 0, wxEXPAND | wxALL, 10);
  _mainWindow->Add(gameWindow, 1, wxEXPAND | wxALL, 10);

  this->SetSizer(_mainWindow);
  this->Fit();
}

void MainGamePanel::buildGameState(GameState *gameState, uuid ownId) {
  LOG("Building game state");
  _gameState     = gameState;
  _ownId         = ownId;
  _currentPlayer = gameState->getCurrentPlayerId();

  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);

  // get player grids
  auto playerGrid = gameState->getPlayerGrid(_ownId);

  // get ships
  std::vector<Ship> playerShips = playerGrid.shipsPlaced;

  std::array<bool, 5> ownShipSunk;
  for (unsigned int i = 0; i < 5; ++i) {
    ownShipSunk[i] = playerShips[i].hasSunken();
  }

  LOG("OwnShipSunk: " + std::to_string(ownShipSunk[0]) + std::to_string(ownShipSunk[1]) +
      std::to_string(ownShipSunk[2]) + std::to_string(ownShipSunk[3]) + std::to_string(ownShipSunk[4]));

  // get shots
  auto ownShots = playerGrid.shotsFired;
  auto oppShots = playerGrid.shotsReceived;

  this->_ownViewGrid->showShips(playerShips);

  this->_ownViewGrid->showShots(oppShots);
  this->_oppViewGrid->showShots(ownShots);

  // turn indicator
  auto text = "It is " + gameState->getPlayer(_currentPlayer)->getName() + "'s turn";
  _turnText->SetLabelText(text);

  // update ship panel
  this->_ownShipPanel->update(ownShipSunk);
  this->_oppShipPanel->update(gameState->getOppShipSunk());
}

void MainGamePanel::displayEmote(EmoteType emote) {
  _currentEmote = new EmotePopup(this, wxDefaultPosition, emote);
  _currentEmote->SetPosition(wxPoint(400, 200));
  _currentEmote->Show();
  this->Layout();
}
