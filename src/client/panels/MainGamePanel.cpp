#include "MainGamePanel.h"

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
  // remove later
  // create players
  Player* me = new Player(uuid::generateRandomUuid(), "Tejas");
  Player* opponent = new Player(uuid::generateRandomUuid(), "Opponent");
  // create game state
  game_state* gameState = new game_state();
  // add players to game state
  gameState->addPlayer(*me);
  gameState->addPlayer(*opponent);
  // create ships
  std::vector<Ship> meShips = {Ship(4, Coordinate(), Ship::Orientation::Horizontal, uuid::generateRandomUuid())};
  std::vector<Ship> opponentShips = {Ship(4, Coordinate(), Ship::Orientation::Horizontal, uuid::generateRandomUuid())};
  // add ships to game state
  gameState->addShips(me->getId(), meShips);
  gameState->addShips(opponent->getId(), opponentShips);

  buildGameState(gameState, me);
}

void MainGamePanel::buildGameState(game_state* gameState, Player* me) {
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);
  
  this->DestroyChildren();

  wxBoxSizer *mainWindow = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *leftSide = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *rightSide = new wxBoxSizer(wxVERTICAL);

  this->_ownViewGrid = new ViewGrid(this, wxPoint(10, 10));
  this->_opponentViewGrid = new ViewGrid(this, wxPoint(430, 10));

  // place grids next to eachother
  leftSide->Add(this->_ownViewGrid, 1, wxEXPAND | wxALL);
  rightSide->Add(this->_opponentViewGrid, 1, wxEXPAND | wxALL);

  // add grids to main window
  mainWindow->Add(leftSide, 1, wxEXPAND | wxALL, 10);
  mainWindow->Add(rightSide, 1, wxEXPAND | wxALL, 10);

  // place ships on own grid
  if (me != nullptr) {
    // get ships (not implemented yet)
    std::vector<Ship> meShips = {Ship(4, Coordinate(), Ship::Orientation::Horizontal, uuid::generateRandomUuid())};
    std::vector<Ship> opponentShips = {Ship(4, Coordinate(), Ship::Orientation::Horizontal, uuid::generateRandomUuid())};
    // place ships on own grid
    this->_ownViewGrid->placeShips(meShips);
    // this->_opponentViewGrid->placeShips(opponentShips);
  }

  this->SetSizerAndFit(mainWindow);
}

void MainGamePanel::buildEmoteList() {
}

void MainGamePanel::buildTurnIndicator() {
}