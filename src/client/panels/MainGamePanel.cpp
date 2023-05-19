#include "MainGamePanel.h"

#include "../GameController.h"
#include "../uiElements/EmotePanel.h"
#include "Logger.h"


MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
  LOG("Constructing MainGamePanel");
  parent->SetMinSize(wxSize(1200, 800));

  _mainWindow = new wxBoxSizer(wxHORIZONTAL);
  _emoteWindow = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* gameWindow = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* turnIndicator = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* grids = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* leftSide = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* rightSide = new wxBoxSizer(wxVERTICAL);

  bool init[5] = {false, false, false, false, false};
  this->_ownShipPanel = new ShipPanel(this, wxDefaultPosition, init);
  this->_oppShipPanel = new ShipPanel(this, wxDefaultPosition, init);

  this->_ownViewGrid  = new ViewGrid( this, ViewGrid::gridtype::own);
  this->_oppViewGrid  = new ViewGrid( this, ViewGrid::gridtype::opp);

  wxBoxSizer* leftTitleSizer = new wxBoxSizer(wxVERTICAL);
  wxStaticText* leftTitle = new wxStaticText(this, wxID_ANY, "Your Ships");
  leftTitleSizer->Add(leftTitle, 1, wxALIGN_CENTER_HORIZONTAL);
  leftSide->Add(leftTitleSizer, 0, wxEXPAND | wxALL, 10);
  leftSide->Add(_ownViewGrid, 1, wxEXPAND | wxALL, 10);
  leftSide->Add(_ownShipPanel, 1, wxEXPAND | wxALL, 10);

  wxBoxSizer* rightTitleSizer = new wxBoxSizer(wxVERTICAL);
  wxStaticText* rightTitle = new wxStaticText(this, wxID_ANY, "Opponent's Ships");
  rightTitleSizer->Add(rightTitle, 1, wxALIGN_CENTER_HORIZONTAL);
  rightSide->Add(rightTitleSizer, 0, wxEXPAND | wxALL, 10);
  rightSide->Add(_oppViewGrid, 1, wxEXPAND | wxALL, 10);
  rightSide->Add(_oppShipPanel, 1, wxEXPAND | wxALL, 10);

  grids->Add(leftSide, 1, wxEXPAND | wxALL, 10);
  grids->Add(rightSide, 1, wxEXPAND | wxALL, 10);

  _turnText = new wxStaticText(this, wxID_ANY, "[TURN INDICATOR]");
  turnIndicator->Add(_turnText, 0, wxALIGN_CENTER_HORIZONTAL, 10);

  gameWindow->Add(turnIndicator, 0, wxEXPAND | wxALL, 10);
  gameWindow->Add(grids, 1, wxEXPAND | wxALL, 10);

  _emotePanel = new EmotePanel(this, wxPoint(10, 10));
  _emoteWindow->Add(_emotePanel, 1, wxEXPAND | wxALL, 10);

  _mainWindow->Add(_emoteWindow, 0, wxEXPAND | wxALL, 10);
  _mainWindow->Add(gameWindow, 1, wxEXPAND | wxALL, 10);

  this->SetSizer(_mainWindow);
  this->Fit();
}

void MainGamePanel::buildGameState(GameState * gameState, uuid ownId) {
  LOG("Building game state");
  _gameState = gameState;
  _ownId = ownId;
  _currentPlayer = gameState->getCurrentPlayerId();

  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);

  //this->DestroyChildren();

  //buildEmoteList();



  // get player grids
  auto playerGrid = gameState->getPlayerGrid(_ownId);

  // get ships
  std::vector<Ship> playerShips = playerGrid.shipsPlaced;
  // std::vector<Ship> oppShips = oppGrid.m_shipsPlaced;
  bool ownShipSunk[5] = {false, false, false, false, false};
  for (int i=0; i<5; ++i) {
    if (playerShips[i].hasSunken()) {
      ownShipSunk[i] = true;
    }
  }

  for (int i=0; i<5; ++i) {
    if (gameState->getOppShipSunk()[i]) {
      LOG("Opponten ship" + std::to_string(i) + " has sunk");
    } else {
      LOG("Opponten ship" + std::to_string(i) + " has not sunk");
    }
  }

  // get shots
  auto ownShots = playerGrid.shotsFired;
  auto oppShots = playerGrid.shotsReceived;


  _mainWindow->Fit(this);
/*
  this->_ownViewGrid->showShips(playerShips);

  this->_ownViewGrid->showShots(oppShots);
  this->_oppViewGrid->showShots(ownShots);
*/
}


void MainGamePanel::buildEmoteList() {
  // this box contains everything
  _mainWindow = new wxBoxSizer(wxHORIZONTAL);
  // box for the emote panel
  _emoteWindow = new wxBoxSizer(wxVERTICAL);


  //this->_emotePanel->Bind(wxEVT_LEFT_DOWN, &MainGamePanel::onEmoteClick, this);
}

void MainGamePanel::displayEmote(EmoteType emote) {
  int emoteId = static_cast<int>(emote);
  LOG("emote id: " + std::to_string(emoteId));
  if (emoteId < 0 || emoteId > 2) {
    LOG("invalid emote id");
    return;
  }
  LOG("I should display emote " + std::to_string(emoteId));
  wxImage image;
  switch (emoteId) {
    case 0:
      image = wxImage("../assets/emotes/large_middlefinger.png");
      break;
    case 1:
      image = wxImage("../assets/emotes/large_gofuckyourself.png");
      break;
    case 2:
      image = wxImage("../assets/emotes/large_mocking.png");
      break;
  }
  _currentEmote = new wxStaticBitmap(this, wxID_ANY, wxBitmap(image), wxPoint(120, 56), wxSize(400, 400), 0);
  // for some reason the image is shown and removed at the next panel update
  _currentEmote = nullptr;
}

void MainGamePanel::buildTurnIndicator(std::string playerName, wxBoxSizer *box) {
  auto text = "It's " + playerName + "'s turn";
  // TODO set text in UI element
}

void MainGamePanel::onMouseClick(wxMouseEvent &event) {
  LOG("registered click in Maingamepanel");
  wxPoint mousePosition = event.GetPosition();
  Coordinate shot = Coordinate{mousePosition.x / 40, mousePosition.y / 40};

  // make sure the click is on the grid
  if (shot.x < 0 || shot.x >= 10 || shot.y < 0 || shot.y >= 10) {
    LOG("Click is not on grid: " + std::to_string(shot.x) + " " + std::to_string(shot.y));
    return;
  }

  // only allow clicks if it is the player's turn
  if (_currentPlayer != _ownId) {
    LOG("not your turn");
    return;
  }
  // temp test
  //AudioPlayer::play(AudioPlayer::BestPirate);
  // end test

  LOG("clicked on cell " + std::to_string(shot.x) + ", " + std::to_string(shot.y));

  // limit shot frequency to one per second to give server time to respond
  auto now = std::chrono::system_clock::now();
  if (now - _lastClick < std::chrono::milliseconds(57)) {
    LOG("too fast");
    return;
  }
  _lastClick = now;

  if (!_gameState->shotIsLegal(_ownId, shot)) {
    LOG("illegal shot");
    return;
  }

  GameController::callShot(shot); // builds callShot request and sends to server
}


void MainGamePanel::onEmoteClick(wxMouseEvent &event) {
  auto now = std::chrono::system_clock::now();
  if (now - _lastClick < std::chrono::milliseconds(57)) {
    LOG("too fast");
    return;
  }
  _lastClick = now;
  wxPoint mousePosition = event.GetPosition();
  mousePosition -= wxPoint(20, 90);
  const int emote = mousePosition.y / 90;
  if(emote < 0 || emote > 2) return;
  LOG("clicked on emote nr " + std::to_string(emote));
  GameController::sendEmote(EmoteType(emote));
}
