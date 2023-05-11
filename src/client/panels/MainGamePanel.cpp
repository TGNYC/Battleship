#include "MainGamePanel.h"

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {}

void MainGamePanel::buildGameState(game_state* gameState, uuid ownId) {
  _gameState = gameState;
  _ownId = ownId;
  _currentPlayer = gameState->getCurrentPlayerId();
  
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);
  
  this->DestroyChildren();

  wxBoxSizer *mainWindow = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *leftSide = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *rightSide = new wxBoxSizer(wxVERTICAL);

  // get player grids
  auto playerGrid = gameState->getPlayerGrid(_ownId);

  // get ships
  std::vector<Ship> playerShips = playerGrid.shipsPlaced;
  // std::vector<Ship> oppShips = oppGrid.m_shipsPlaced;

  // get shots
  auto ownShots = playerGrid.shotsFired;
  auto oppShots = playerGrid.shotsReceived;

  this->_ownShipPanel = new ShipPanel(this, wxPoint( 10, 430), playerShips);
  // TODO: find a way to do this without requiring acces to opponent ship vector
  this->_oppShipPanel = new ShipPanel(this, wxPoint(430, 430), playerShips);

  this->_ownViewGrid = new ViewGrid(this, wxPoint( 10, 10));
  this->_oppViewGrid = new ViewGrid(this, wxPoint(430, 10));
  
  this->_ownViewGrid->showShips(playerShips);

  this->_oppViewGrid->showShots(ownShots);
  this->_ownViewGrid->showShots(oppShots);

  // place grids next to eachother
  leftSide->Add(_ownViewGrid, 1, wxEXPAND | wxALL);
  rightSide->Add(_oppViewGrid, 1, wxEXPAND | wxALL);

  leftSide->Add(_ownShipPanel, 0, wxEXPAND | wxALL, 0);
  rightSide->Add(_oppShipPanel, 0, wxEXPAND | wxALL, 0);

  // add grids to main window
  mainWindow->Add(leftSide, 1, wxEXPAND | wxALL, 10);
  mainWindow->Add(rightSide, 1, wxEXPAND | wxALL, 10);

  this->_oppViewGrid->Bind(wxEVT_LEFT_DOWN, &MainGamePanel::onMouseClick, this);

  this->SetSizerAndFit(mainWindow);
}

void MainGamePanel::buildEmoteList() {
}

void MainGamePanel::buildTurnIndicator() {
}

void MainGamePanel::onMouseClick(wxMouseEvent &event) {
  // only allow clicks if it is the player's turn
  if (_currentPlayer != _ownId) {
    std::cout << "not your turn" << std::endl;
    return;
  }
  // temp test
  AudioPlayer::play(AudioPlayer::BestPirate);
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