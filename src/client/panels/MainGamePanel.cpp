#include "MainGamePanel.h"

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {}

void MainGamePanel::buildGameState(game_state* gameState, uuid ownId) {
  _gameState = gameState;
  _ownId = ownId;
  _currentPlayer = gameState->getCurrentPlayerId();
  
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);
  
  this->DestroyChildren();

  // this box contains everything
  wxBoxSizer* _mainWindow = new wxBoxSizer(wxVERTICAL);
  // this shows who's turn it is via text
  wxBoxSizer* turnIndicator = new wxBoxSizer(wxVERTICAL);
  // this contains both the grids and the shipPanels
  wxBoxSizer* grids = new wxBoxSizer(wxHORIZONTAL);
  // this contains the own viewGrid and shipPanels
  wxBoxSizer* leftSide = new wxBoxSizer(wxVERTICAL);
  // this contains the opponent's viewGrid and shipPanels
  wxBoxSizer* rightSide = new wxBoxSizer(wxVERTICAL);

  // get player grids
  auto playerGrid = gameState->getPlayerGrid(_ownId);

  // get ships
  std::vector<Ship> playerShips = playerGrid.shipsPlaced;
  // std::vector<Ship> oppShips = oppGrid.m_shipsPlaced;

  // get shots
  auto ownShots = playerGrid.shotsFired;
  auto oppShots = playerGrid.shotsReceived;

  this->_ownShipPanel = new ShipPanel(this, wxPoint( 10, 470), playerShips);
  // TODO: find a way to do this without requiring acces to opponent ship vector
  this->_oppShipPanel = new ShipPanel(this, wxPoint(430, 470), playerShips);

  this->_ownViewGrid  = new ViewGrid( this, wxPoint( 10, 50), ViewGrid::gridtype::own);
  this->_oppViewGrid  = new ViewGrid( this, wxPoint(430, 50), ViewGrid::gridtype::opp);
  
  this->_ownViewGrid->showShips(playerShips);

  this->_ownViewGrid->showShots(oppShots);
  this->_oppViewGrid->showShots(ownShots);

  this->_oppViewGrid->Bind(wxEVT_LEFT_DOWN, &MainGamePanel::onMouseClick, this);

  wxStaticText* leftTitle = new wxStaticText(this, wxID_ANY, "Your Ships");
  leftSide->Add(leftTitle, 0, wxALIGN_CENTER, 10);

  leftSide->Add(_ownViewGrid, 0, wxALIGN_CENTER | wxBOTTOM, 10);
  leftSide->Add(_ownShipPanel, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

  wxStaticText* rightTitle = new wxStaticText(this, wxID_ANY, "Opponent's Ships");
  rightSide->Add(rightTitle, 0, wxALIGN_CENTER, 10);

  rightSide->Add(_oppViewGrid, 0, wxALIGN_CENTER | wxBOTTOM, 10);
  rightSide->Add(_oppShipPanel, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

  // place grids next to eachother
  grids->Add(leftSide, 0, wxALL, 10);
  grids->Add(rightSide, 0, wxALL, 10);

  // add grids to main window
  buildTurnIndicator(_gameState->getPlayerName(_currentPlayer), turnIndicator);
  _mainWindow->Add(turnIndicator, 0, wxALIGN_CENTER, 10);
  _mainWindow->Add(grids, 0, wxALIGN_CENTER, 10);

  this->SetSizerAndFit(_mainWindow);
}

void MainGamePanel::buildEmoteList() {
}

void MainGamePanel::buildTurnIndicator(std::string playerName, wxBoxSizer *box) {
  auto text = "It's " + playerName + "'s turn";
  wxStaticText* turnText = new wxStaticText(this, wxID_ANY, text);
  box->Add(turnText, 0, wxALIGN_TOP, 10);
}

void MainGamePanel::onMouseClick(wxMouseEvent &event) {
  // only allow clicks if it is the player's turn
  if (_currentPlayer != _ownId) {
    std::cout << "not your turn" << std::endl;
    return;
  }
  // temp test
  //AudioPlayer::play(AudioPlayer::BestPirate);
  // end test

  wxPoint mousePosition = event.GetPosition();
  mousePosition -= _oppViewGrid->GetPosition();
  
  Coordinate shot = Coordinate{mousePosition.x / 40, mousePosition.y / 40};

  std::cout << "clicked on cell " << shot.x << ", " << shot.y << std::endl;

  // limit shot frequency to one per second to give server time to respond
  auto now = std::chrono::system_clock::now();
  if (now - _lastShot < std::chrono::seconds(1)) {
    std::cout << "too fast" << std::endl;
    return;
  }
  _lastShot = now;

  if (!_gameState->shotIsLegal(_ownId, shot)) {
    std::cout << "illegal shot" << std::endl;
    return;
  }

  // TODO: Send shot to server and wait for response
}