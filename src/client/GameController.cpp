#include "GameController.h"

// initialize static variables
GameWindow *GameController::_gameWindow = nullptr;
ConnectionPanel *GameController::_connectionPanel = nullptr;
SetupPanel *GameController::_setupPanel = nullptr;
MainGamePanel *GameController::_mainGamePanel = nullptr;


void GameController::init(GameWindow* gameWindow) {
  GameController::_gameWindow = gameWindow;

  // setup panels
  GameController::_connectionPanel = new ConnectionPanel(gameWindow);
  GameController::_setupPanel = new SetupPanel(gameWindow);
  GameController::_mainGamePanel = new MainGamePanel(gameWindow);

  // hide panels
  GameController::_connectionPanel->Show(false);
  GameController::_setupPanel->Show(false);
  GameController::_mainGamePanel->Show(false);

  // start of game: show connection panel
  GameController::_gameWindow->showPanel(GameController::_connectionPanel);

}

void GameController::connectToServer() {
  // get values
  wxString inputServerAddress = GameController::_connectionPanel->getServerAddress().Trim();
  wxString inputServerPort = GameController::_connectionPanel->getServerPort().Trim();
  wxString inputPlayerName = GameController::_connectionPanel->getUserName().Trim();

  // check that all values were provided
  if(inputServerAddress.IsEmpty()) {
    GameController::showError("Input error", "Please provide the server's address");
    return;
  }
  if(inputServerPort.IsEmpty()) {
    GameController::showError("Input error", "Please provide the server's port number");
    return;
  }
  if(inputPlayerName.IsEmpty()) {
    GameController::showError("Input error", "Please enter your desired player name");
    return;
  }

}

void GameController::enterSetupPhase() {
  // show setup panel
  GameController::_gameWindow->showPanel(GameController::_setupPanel);
}

void GameController::startGame() {


}

void GameController::callShot() {
}

void GameController::sendEmote() {
}

void GameController::showError(const std::string& title, const std::string& message) {
  std::cout << "[" << title << "] " << message << std::endl;
}
void GameController::showGameOverMessage() {
}
