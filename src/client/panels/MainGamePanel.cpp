#include "MainGamePanel.h"

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
  // remove later
  // create players
  Player* me = new Player(uuid::generateRandomUuid(), "Tejas");
  Player* opponent = new Player(uuid::generateRandomUuid(), "Opponent");
  // create game state
  game_state* gameState = new game_state(game_state::Type::ClientState);
  // add players to game state
  gameState->addPlayer(*me);
  gameState->addPlayer(*opponent);
  // create ships
  std::vector<Ship> ownShips = {Ship(4, Coordinate(), Ship::Orientation::Horizontal, uuid::generateRandomUuid())};
  std::vector<Ship> oppShips = {Ship(4, Coordinate(), Ship::Orientation::Horizontal, uuid::generateRandomUuid())};
  // add ships to game state
  gameState->addShips(me->getId(), ownShips);
  gameState->addShips(opponent->getId(), oppShips);

  buildGameState(gameState, me);
}

void MainGamePanel::buildGameState(game_state* gameState, Player* me) {
  this->_gameState = gameState;
  this->_me = me;
  
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);
  
  this->DestroyChildren();

  wxBoxSizer *mainWindow = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *leftSide = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *rightSide = new wxBoxSizer(wxVERTICAL);

  this->_ownViewGrid = new ViewGrid(this, wxPoint(10, 10));
  this->_oppViewGrid = new ViewGrid(this, wxPoint(430, 10));

  // place grids next to eachother
  leftSide->Add(this->_ownViewGrid, 1, wxEXPAND | wxALL);
  rightSide->Add(this->_oppViewGrid, 1, wxEXPAND | wxALL);

  // get ships (not implemented yet)
  std::vector<Ship> ownShips = {
    Ship(5, Coordinate{0, 0}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()),
    Ship(4, Coordinate{6, 0}, Ship::Orientation::Vertical, uuid::generateRandomUuid()),
    Ship(3, Coordinate{0, 2}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()),
    Ship(3, Coordinate{4, 2}, Ship::Orientation::Vertical, uuid::generateRandomUuid()),
    Ship(2, Coordinate{8, 2}, Ship::Orientation::Vertical, uuid::generateRandomUuid()),
  };
  std::vector<Ship> oppShips = {
    Ship(5, Coordinate{0, 1}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()),
    Ship(4, Coordinate{6, 1}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()),
    Ship(3, Coordinate{0, 3}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()),
    Ship(3, Coordinate{4, 3}, Ship::Orientation::Vertical, uuid::generateRandomUuid()),
    Ship(2, Coordinate{8, 3}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()),
  };
  oppShips[2].hit(Coordinate{0, 3});
  oppShips[2].hit(Coordinate{1, 3});
  oppShips[2].hit(Coordinate{2, 3});
  
  this->_ownViewGrid->showShips(ownShips);
  // this->_opponentViewGrid->showShips(oppShips);

  int ownshots[10][10] = {{0}};
  ownshots[0][3] = 2;
  ownshots[1][3] = 2;
  ownshots[2][3] = 2;
  ownshots[5][5] = 1;
  int oppshots[10][10] = {{0}};
  oppshots[0][0] = 2;
  oppshots[1][1] = 1;
  oppshots[9][1] = 1;
  oppshots[5][8] = 1;
  this->_oppViewGrid->showShots(ownshots);
  this->_ownViewGrid->showShots(oppshots);

  this->_ownShipPanel = new ShipPanel(this, wxPoint(10, 430), ownShips);
  this->_oppShipPanel = new ShipPanel(this, wxPoint(430, 430), oppShips);

  leftSide->Add(_ownShipPanel, 0, wxEXPAND | wxALL, 0);
  rightSide->Add(_oppShipPanel, 0, wxEXPAND | wxALL, 0);

  // add grids to main window
  mainWindow->Add(leftSide, 1, wxEXPAND | wxALL, 10);
  mainWindow->Add(rightSide, 1, wxEXPAND | wxALL, 10);

  this->SetSizerAndFit(mainWindow);
}

void MainGamePanel::buildEmoteList() {
}

void MainGamePanel::buildTurnIndicator() {
}