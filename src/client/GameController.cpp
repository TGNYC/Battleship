#include "GameController.h"
#include "AudioPlayer.h"
#include "ClientNetworkManager.h"
#include "Logger.h"
#include "network/requests/CallShot.h"
#include "network/requests/JoinGame.h"
#include "network/requests/QuitGame.h"
#include "network/requests/SendEmote.h"
#include "network/requests/StartGame.h"

// initialize static variables
GameWindow                                        *GameController::_gameWindow      = nullptr;
ConnectionPanel                                   *GameController::_connectionPanel = nullptr;
SetupPanel                                        *GameController::_setupPanel      = nullptr;
MainGamePanel                                     *GameController::_mainGamePanel   = nullptr;
SetupManager                                      *GameController::_setupManager    = nullptr;
Player                                            *GameController::_me              = nullptr;
GameState                                         *GameController::_gameState       = nullptr;
std::chrono::time_point<std::chrono::system_clock> GameController::_lastClick;

/**
 * @brief Constructor for GameController. Initializes different panels
 * @param gameWindow
 */
void GameController::init(GameWindow *gameWindow) {
  LOG("initializing controller");
  GameController::_gameWindow = gameWindow;

  // setup panels
  GameController::_connectionPanel = new ConnectionPanel(gameWindow);
  GameController::_setupPanel      = new SetupPanel(gameWindow);
  GameController::_mainGamePanel   = new MainGamePanel(gameWindow);

  // hide panels
  GameController::_connectionPanel->Show(false);
  GameController::_setupPanel->Show(false);
  GameController::_mainGamePanel->Show(false);

  // start of game: show connection panel
  GameController::_gameWindow->showPanel(GameController::_connectionPanel);
  // GameController::startGame(); // TODO: should be the function to be called @nico: no? startGame is called when
  // receiving startGameSuccess from server

  _lastClick = std::chrono::system_clock::now();
}

/**
 * @brief Function that is called when connect button on ConnectionPanel is clicked. Will try to connect to the server
 */
void GameController::connectToServer() {
  // get values
  wxString inputServerAddress = GameController::_connectionPanel->getServerAddress().Trim();
  wxString inputServerPort    = GameController::_connectionPanel->getServerPort().Trim();
  wxString inputPlayerName    = GameController::_connectionPanel->getUserName().Trim();

  // check that all values were provided
  if (inputServerAddress.IsEmpty()) {
    GameController::showError("Input error", "Please provide the server's address", true);
    return;
  }
  if (inputServerPort.IsEmpty()) {
    GameController::showError("Input error", "Please provide the server's port number", true);
    return;
  }
  if (inputPlayerName.IsEmpty()) {
    GameController::showError("Input error", "Please enter your desired player name", true);
    return;
  }

  // convert host from wxString to std::string
  std::string host = inputServerAddress.ToStdString();

  // convert port from wxString to uint16_t
  unsigned long portAsLong;
  if (!inputServerPort.ToULong(&portAsLong) || portAsLong > 65535) {
    GameController::showError("Connection error", "Invalid port", true);
    return;
  }
  uint16_t port = static_cast<uint16_t>(portAsLong);

  // convert player name from wxString to std::string
  std::string playerName = inputPlayerName.ToStdString();

  // connect to network
  ClientNetworkManager::init(host, port);

  // send request to join game
  LOG("sending join request");
  GameController::_me = new Player(uuid::generateRandomUuid(), playerName);
  JoinGame request    = JoinGame(GameController::_me->getId(), GameController::_me->getName());

  ClientNetworkManager::sendRequest(request);
}

/**
 * @beief function that is called when server responds with JoinGameSuccess response. Will show setup panel.
 */
void GameController::enterSetupPhase() {
  // show setup panel
  GameController::_setupManager = new SetupManager();
  GameController::_gameWindow->showPanel(GameController::_setupPanel);
}

/**
 * @brief Function that is called when server responds with StartGameSuccess. Will show main game panel.
 */
void GameController::startGame(const StartGameSuccess &response) { // called by ResponseListenerThread
  LOG("Game is starting");
  // adding opponent to game state
  assert(response.players.size() == 2);
  Player opponent = response.players.at(0);
  if (opponent.getId() == _me->getId()) {
    opponent = response.players.at(1);
  }
  _gameState->addPlayer(opponent);
  // set starting player
  LOG("Starting game state");
  assert(_gameState != nullptr);
  assert(_gameState->start(response.startingPlayerId));
  // show GUI
  GameController::_gameWindow->showPanel(GameController::_mainGamePanel);
  GameController::_mainGamePanel->buildGameState(GameController::_gameState, GameController::_me->getId());
  GameController::_gameWindow->Layout();
}

void GameController::handleGameEvent(const GameEvent &event) {
  _gameState->updateBoards(event);
  uuid currentPlayerId = _gameState->getCurrentPlayerId();
  _mainGamePanel->buildGameState(_gameState, _me->getId());
}

void GameController::callShot(Coordinate position) {
  LOG("Calling shot on position " + std::to_string(position.x) + "," + std::to_string(position.y));
  // TODO: Call ShotIsLegal & limit shot frequency
  // only current player can shoot
  if (_gameState->getCurrentPlayerId() != _me->getId()) {
    LOG("not your turn");
    return;
  }
  // limit shot frequency
  auto now = std::chrono::system_clock::now();
  if (now - _lastClick < std::chrono::milliseconds(100)) { // 57
    LOG("too fast");
    return;
  }
  _lastClick = now;
  // make sure shot is legal
  if (!_gameState->shotIsLegal(_me->getId(), position)) {
    LOG("illegal shot");
    return;
  }
  // shot is ok, send to server
  CallShot request = CallShot(_me->getId(), position);
  ClientNetworkManager::sendRequest(request);
}

void GameController::sendEmote(EmoteType emote) {
  SendEmote request = SendEmote(_me->getId(), emote);
  ClientNetworkManager::sendRequest(request);
}

void GameController::showEmote(EmoteEvent emoteEvent) {
  EmoteType   emote = emoteEvent.emote;
  std::string file  = EmoteHandler::getImage(emote);
  _mainGamePanel->displayEmote(emote);
  AudioPlayer::play(EmoteHandler::getSound(emote));
}

void GameController::showError(const std::string &title, const std::string &message, bool popup) {
  std::cout << "ERROR [" << title << "] " << message << std::endl;
  if (popup)
    wxMessageBox(message, title, wxOK | wxICON_ERROR);
}

void GameController::gameOver(uuid winnerId) {
  _gameState->finish();
  std::string message = "\n";
  if (winnerId == _me->getId()) {
    message += "You won!";
    // AudioPlayer::play(AudioPlayer::Victory);
  } else {
    message += "You lost!";
    // AudioPlayer::play(AudioPlayer::Defeat);
  }
  wxMessageBox(message, "Game Over", wxOK | wxICON_INFORMATION);
  // Send player back to connection panel
  // TODO: Fix memory leaks, shut down listenerThread
  GameController::init(_gameWindow);
}

void GameController::playerReady() {
  if (!_setupManager->placedAllShips()) {
    GameController::showError("Setup error", "Please place all ships before clicking ready", true);
    return;
  }

  // generate GameState
  LOG("Generating GameState");
  _gameState = new GameState(GameState::Type::ClientState);
  _gameState->addPlayer(*_me);
  _gameState->addShips(_me->getId(), _setupManager->_ships_placed);
  LOG("Printing ship ids...");
  for (auto ship : _gameState->getPlayerGrid(_me->getId()).shipsPlaced) {
    LOG(ship.getId().ToString());
  }

  // todo: maybe display some waiting for other player information
  LOG("Sending request to server. You might need to wait for your opponent to be ready.");

  // send request to start game
  StartGame request = StartGame(_me->getId(), _setupManager->_ships_placed);
  ClientNetworkManager::sendRequest(request);

  // disable button such that player cannot click it again
  GameController::_setupPanel->getReadyButton()->Disable();

  // display text that ship placement was submitted and that player is waiting for opponent
  GameController::_setupPanel->getReadyText()->SetLabel("Ship placement submitted.\nWaiting for opponent...");
  GameController::_setupPanel->Layout();
}

wxEvtHandler *GameController::getMainThreadEventHandler() {
  return GameController::_gameWindow->GetEventHandler();
}

void GameController::quitGame() {
  // send quit game request
  LOG("Sending quit game request");
  QuitGame request = QuitGame(_me->getId());
  ClientNetworkManager::sendRequest(request);
}

void GameController::handleQuitGameEvent(uuid quitterId) {
  if (quitterId != _me->getId()) {
    std::string message = "Your opponent left the game\n";
    wxMessageBox(message, "Opponent left", wxOK | wxICON_INFORMATION);
    LOG("resetting client...");
    GameController::init(_gameWindow);
  }
}
