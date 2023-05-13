#include "GameController.h"
#include "ClientNetworkManager.h"
#include "network/requests/JoinGame.h"
#include "network/requests/StartGame.h"

// initialize static variables
GameWindow      *GameController::_gameWindow      = nullptr;
ConnectionPanel *GameController::_connectionPanel = nullptr;
SetupPanel      *GameController::_setupPanel      = nullptr;
MainGamePanel   *GameController::_mainGamePanel   = nullptr;
SetupManager    *GameController::_setupManager    = nullptr;
Player          *GameController::_me              = nullptr;
game_state      *GameController::_gameState       = nullptr;

void GameController::init(GameWindow *gameWindow) {
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
  GameController::_gameWindow->showPanel(GameController::_connectionPanel); // TODO: CHANGE BACK, only for testing maingamepanel
  //GameController::startGame();
}

void GameController::connectToServer() {
  // get values
  wxString inputServerAddress = GameController::_connectionPanel->getServerAddress().Trim();
  wxString inputServerPort    = GameController::_connectionPanel->getServerPort().Trim();
  wxString inputPlayerName    = GameController::_connectionPanel->getUserName().Trim();

  // check that all values were provided
  if (inputServerAddress.IsEmpty()) {
    GameController::showError("Input error", "Please provide the server's address");
    return;
  }
  if (inputServerPort.IsEmpty()) {
    GameController::showError("Input error", "Please provide the server's port number");
    return;
  }
  if (inputPlayerName.IsEmpty()) {
    GameController::showError("Input error", "Please enter your desired player name");
    return;
  }

  // convert host from wxString to std::string
  std::string host = inputServerAddress.ToStdString();

  // convert port from wxString to uint16_t
  unsigned long portAsLong;
  if (!inputServerPort.ToULong(&portAsLong) || portAsLong > 65535) {
    GameController::showError("Connection error", "Invalid port");
    return;
  }
  uint16_t port = (uint16_t)portAsLong;

  // convert player name from wxString to std::string
  std::string playerName = inputPlayerName.ToStdString();

  // connect to network
  ClientNetworkManager::init(host, port);

  // send request to join game
  GameController::_me = new Player(uuid::generateRandomUuid(), playerName);
  JoinGame request    = JoinGame(GameController::_me->getId(), GameController::_me->getName());
  ClientNetworkManager::sendRequest(request);

  // enter set-up phase if the JoinGame response indicates success
//  GameController::enterSetupPhase();

}

void GameController::enterSetupPhase() {
  // show setup panel
  GameController::_setupManager = new SetupManager();
  GameController::_gameWindow->showPanel(GameController::_setupPanel);
}

void GameController::startGame() { // called by ResponseListenerThread
  std::cout << "Player is ready. Game is starting." << std::endl;
  GameController::_gameWindow->showPanel(GameController::_mainGamePanel);
  GameController::_mainGamePanel->buildGameState(GameController::_gameState, GameController::_me->getId());
  GameController::_gameWindow->Layout();
}

void GameController::handleGameEvent(const GameEvent &event) {
  _gameState->updateBoards(event);
  uuid currentPlayerId = _gameState->getCurrentPlayerId();
  _mainGamePanel->buildGameState(_gameState, _me->getId());
}

void GameController::callShot() {}

void GameController::sendEmote() {}

void GameController::showEmote(EmoteEvent emoteEvent) {
  EmoteType emote = emoteEvent.emote;
  std::string file = EmoteHandler::getImage(emote);
  //TODO call a function in MainGamePanel to display the png file
}

void GameController::showError(const std::string &title, const std::string &message) {
  std::cout << "[" << title << "] " << message << std::endl;
}
void GameController::showGameOverMessage() {}
void GameController::playerReady() {
  // generate GameState
  _gameState = new game_state(game_state::Type::ClientState);
  _gameState->addPlayer(*_me);
  _gameState->addShips(_me->getId(), _setupManager->_ships_placed);


  GameController::startGame(); // TODO: REMOVE - ONLY FOR TESTING
  return;

  // todo: maybe display some waiting for other player information
  std::cout << "Sending request to server. You might need to wait for your opponent to be ready." << std::endl;

  // send request to start game
  StartGame request = StartGame(_me->getId(), _setupManager->_ships_placed);
  ClientNetworkManager::sendRequest(request);
}
wxEvtHandler *GameController::getMainThreadEventHandler() {
  return GameController::_gameWindow->GetEventHandler();
}
