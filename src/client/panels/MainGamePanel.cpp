#include "MainGamePanel.h"
#include <iostream>

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
  // remove later
  // create players
  Player* me = new Player(uuid::generateRandomUuid(), "Me");
  Player* opponent = new Player(uuid::generateRandomUuid(), "Opponent");
  // create game state
  game_state* gameState = new game_state();
  // add players to game state
  gameState->addPlayer(*me);
  gameState->addPlayer(*opponent);
  // create ships
  std::vector<Ship> ownShips = {
    Ship(5, Coordinate{0, 0}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()),
    Ship(4, Coordinate{6, 0}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()),
    Ship(3, Coordinate{0, 2}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()),
    Ship(3, Coordinate{4, 2}, Ship::Orientation::Horizontal, uuid::generateRandomUuid()),
    Ship(2, Coordinate{8, 2}, Ship::Orientation::Horizontal, uuid::generateRandomUuid())
  };
  std::vector<Ship> oppShips = ownShips;
  // add ships to game state
  gameState->addShips(me->getId(), ownShips);
  gameState->addShips(opponent->getId(), oppShips);

  buildGameState(gameState, me);
}

void MainGamePanel::buildGameState(game_state* gameState, Player* me) {
  // not sure if we should delete the old game state and player 
  // it sometimes leads to segfaults so maybe not
  // if (this->_gameState != gameState && this->_gameState != nullptr) delete this->_gameState;
  this->_gameState = gameState;
  // if (this->_me != me && this->_me != nullptr) delete this->_me;
  this->_me = me;
  _ownId = uuid(this->_me->getId());
  
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);
  
  this->DestroyChildren();

  wxBoxSizer *mainWindow = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *leftSide = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *rightSide = new wxBoxSizer(wxVERTICAL);

  // get player grids
  auto ownGrid = this->_gameState->getPlayerGrid(_ownId);
  auto oppGrid = this->_gameState->getPlayerGrid(this->_gameState->getOtherPlayer(_ownId));

  // get ships
  std::vector<Ship> ownShips = ownGrid.m_shipsPlaced;
  std::vector<Ship> oppShips = oppGrid.m_shipsPlaced;

  // get shots
  auto ownshots = ownGrid.shotsFired;
  auto oppshots = oppGrid.shotsFired;

  // delete this->_ownShipPanel;
  this->_ownShipPanel = new ShipPanel(this, wxPoint( 10, 430), ownShips);
  // delete this->_oppShipPanel;
  this->_oppShipPanel = new ShipPanel(this, wxPoint(430, 430), oppShips);

  // delete this->_ownViewGrid;
  this->_ownViewGrid = new ViewGrid(this, wxPoint( 10, 10), &ownGrid);
  // delete this->_oppViewGrid;
  this->_oppViewGrid = new ViewGrid(this, wxPoint(430, 10), &oppGrid);
  
  this->_ownViewGrid->showShips();

  this->_oppViewGrid->showShots();
  this->_ownViewGrid->showShots();

  // place grids next to eachother
  leftSide->Add(this->_ownViewGrid, 1, wxEXPAND | wxALL);
  rightSide->Add(this->_oppViewGrid, 1, wxEXPAND | wxALL);

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
  wxPoint mousePosition = event.GetPosition();
  mousePosition -= this->_oppViewGrid->GetPosition();
  
  Coordinate shot = Coordinate{mousePosition.x / 40, mousePosition.y / 40};

  std::cout << "clicked on cell " << shot.x << ", " << shot.y << std::endl;

  // this only works if we can get a non-const reference of the player grid
  bool hit = false;
  bool sunk = false;
  for (Ship& ship : this->_gameState->getPlayerGrid(this->_gameState->getOtherPlayer(_ownId)).m_shipsPlaced) {
    if (ship.hit(shot)) {
      hit = true;
      if (ship.hasSunken()) {
        sunk = true;
      }
      break;
    }
  }

  if (hit) {
    std::cout << "hit";
    if (sunk) {
      std::cout << " and sunk";
    }
  } else {
    std::cout << "miss";
  }
  std::cout << std::endl;

  this->_gameState->getPlayerGrid(this->_gameState->getOtherPlayer(_ownId)).shotsReceived[shot.x][shot.y] = hit ? 2 : 1;

  buildGameState(this->_gameState, this->_me);
}