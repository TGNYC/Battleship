#include "MainGamePanel.h"

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {}

void MainGamePanel::buildGameState(game_state* gameState, Player& player) {
  _gameState = gameState;
  _ownId = player.getId();
  
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);
  
  this->DestroyChildren();

  wxBoxSizer *mainLayout = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *twoGridLayout = new wxBoxSizer(wxHORIZONTAL);
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
  twoGridLayout->Add(leftSide, 1, wxEXPAND | wxALL, 10);
  twoGridLayout->Add(rightSide, 1, wxEXPAND | wxALL, 10);
  this->SetSizerAndFit(twoGridLayout);

  /*
  mainLayout->Add(twoGridLayout, 1, wxEXPAND | wxALL, 10);

  // add a view of 5 emotes below the grids
  wxBoxSizer *emoteLayout = new wxBoxSizer(wxHORIZONTAL);

  wxStaticBitmap *emotes[5];

  for (int i = 0; i < 5; i++) {
    emotes[i] = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxImage("../assets/emotes/emote.png"), wxBITMAP_TYPE_PNG));
    emoteLayout->Add(emotes[i], 1, wxEXPAND | wxALL, 10);
  }

  mainLayout->Add(emoteLayout, 0, wxEXPAND | wxALL, 10);

  this->SetSizerAndFit(mainLayout);
  */




  this->_oppViewGrid->Bind(wxEVT_LEFT_DOWN, &MainGamePanel::onMouseClick, this);


}

void MainGamePanel::buildEmoteList() {
}

void MainGamePanel::buildTurnIndicator() {
}

void MainGamePanel::onMouseClick(wxMouseEvent &event) {

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