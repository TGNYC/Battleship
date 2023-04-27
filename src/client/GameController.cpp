#include "GameController.h"

void GameController::init(GameWindow* gameWindow) {
  GameController::_gameWindow = gameWindow;

  GameController::_connectionPanel = new ConnectionPanel(gameWindow);
  GameController::_mainGamePanel = new MainGamePanel(gameWindow);

  GameController::_connectionPanel->Show(false);
  GameController::_mainGamePanel->Show(false);

  GameController::_gameWindow->showPanel(GameController::_connectionPanel);

  // set status bar
}

void GameController::connectToServer() {
}

void GameController::startGame() {
}

void GameController::callShot() {
}

void GameController::sendEmote() {
}

void GameController::showError(const std::string& title, const std::string& message) {
}

void GameController::showGameOverMessage() {
}