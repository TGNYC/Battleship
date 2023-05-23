#include "MainGamePanel.h"

#include "../GameController.h"
#include "../uiElements/EmotePanel.h"
#include "Logger.h"

MainGamePanel::MainGamePanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
  LOG("Constructing MainGamePanel");
  parent->SetMinSize(wxSize(1200, 800));
  // For some reason, the ShipPanels take up way too much space after this->SetSizer(_mainWindow) on line 61 is called. 
  // Before, they have a size of 400x100, afterwards it's 400x400. 
  // This limits the maximum size of the window, but it's not a good fix.
  parent->SetMaxSize(wxSize(1200, 800));

  _mainWindow = new wxBoxSizer(wxHORIZONTAL);
  _emoteWindow = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* gameWindow = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* turnIndicator = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* grids = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* leftSide = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* rightSide = new wxBoxSizer(wxVERTICAL);

  std::array<bool, 5> init = {false, false, false, false, false};
  this->_ownShipPanel = new ShipPanel(this, wxDefaultPosition, init);
  this->_oppShipPanel = new ShipPanel(this, wxDefaultPosition, init);

  this->_ownViewGrid  = new ViewGrid( this, ViewGrid::gridtype::own);
  this->_oppViewGrid  = new ViewGrid( this, ViewGrid::gridtype::opp);

  wxBoxSizer* leftTitleSizer = new wxBoxSizer(wxVERTICAL);
  wxStaticText* leftTitle = new wxStaticText(this, wxID_ANY, "Your Ships");
  leftTitleSizer->Add(leftTitle, 1, wxALIGN_CENTER_HORIZONTAL);
  leftSide->Add(leftTitleSizer, 0, wxEXPAND | wxTOP, 10);
  leftSide->Add(_ownViewGrid, 1, wxEXPAND | wxALL, 10);
  leftSide->Add(_ownShipPanel, 1, wxEXPAND | wxALL, 10);

  wxBoxSizer* rightTitleSizer = new wxBoxSizer(wxVERTICAL);
  wxStaticText* rightTitle = new wxStaticText(this, wxID_ANY, "Opponent's Ships");
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

  // BINDINGS
  //_oppViewGrid->Bind(wxEVT_LEFT_DOWN, &MainGamePanel::onMouseClick);


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

  // get player grids
  auto playerGrid = gameState->getPlayerGrid(_ownId);

  // get ships
  std::vector<Ship> playerShips = playerGrid.shipsPlaced;
  // std::vector<Ship> oppShips = oppGrid.m_shipsPlaced;

  std::array<bool, 5> ownShipSunk;
  for (int i = 0; i < 5; ++i) {
    ownShipSunk[i] = playerShips[i].hasSunken();
  }

  LOG("OwnShipSunk: " + std::to_string(ownShipSunk[0]) + std::to_string(ownShipSunk[1]) + std::to_string(ownShipSunk[2]) + std::to_string(ownShipSunk[3]) + std::to_string(ownShipSunk[4]));

  // get shots
  auto ownShots = playerGrid.shotsFired;
  auto oppShots = playerGrid.shotsReceived;

  this->_ownViewGrid->showShips(playerShips);

  this->_ownViewGrid->showShots(oppShots);
  this->_oppViewGrid->showShots(ownShots);

  // turn indicator
  auto text = "It's " + gameState->getPlayer(_currentPlayer).getName() + "'s turn";
  _turnText->SetLabelText(text);

  // update ship panel
  this->_ownShipPanel->update(ownShipSunk);
  this->_oppShipPanel->update(gameState->getOppShipSunk());

}

void MainGamePanel::displayEmote(EmoteType emote) {
  _currentEmote = new EmotePopup(this, wxDefaultPosition, emote);
  // _currentEmote->CenterOnParent();
  _currentEmote->SetPosition(wxPoint(400, 200));
  _currentEmote->Show();
  this->Layout();
  /*
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
  _currentEmote = new wxStaticBitmap(this, wxID_ANY, wxBitmap(image), wxPoint(180, 86), wxSize(400, 400), 0);
  _currentEmote->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent &event) {
    LOG("Hide current emote");
    this->_currentEmote->Destroy();
  });
  */
}

/*
void MainGamePanel::onMouseClick(wxMouseEvent &event) {
  LOG("registered click in Maingamepanel");
  wxPoint mousePosition = event.GetPosition();
  LOG("clicked at: " + std::to_string(mousePosition.x) + ", " + std::to_string(mousePosition.y));
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
*/