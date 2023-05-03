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

  wxBoxSizer *horizontalLayout = new wxBoxSizer(wxHORIZONTAL);

  this->_ownViewGrid = new ViewGrid(this);
  this->_opponentViewGrid = new ViewGrid(this);

  horizontalLayout->Add(this->_ownViewGrid, 1, wxDEFAULT, 10);
  horizontalLayout->Add(this->_opponentViewGrid, 1, wxDEFAULT, 10);

  // place ships on own grid
  if (me != nullptr) {
    // get ships (not implemented yet)
    std::vector<Ship> meShips = {Ship(4, Coordinate(), Ship::Orientation::Horizontal, uuid::generateRandomUuid())};
    std::vector<Ship> opponentShips = {Ship(4, Coordinate(), Ship::Orientation::Horizontal, uuid::generateRandomUuid())};
    // place ships on own grid
    this->_ownViewGrid->placeShips(meShips);
  }

  this->SetSizerAndFit(horizontalLayout);
}

void MainGamePanel::buildEmoteList() {
}

void MainGamePanel::buildTurnIndicator() {
}