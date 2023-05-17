#include "Battleship.h"

#include "GameWindow.h"
#include <memory>
#include "panels/ConnectionPanel.h"
#include "panels/SetupPanel.h"
#include "GameController.h"
#include "Logger.h"

auto Battleship::OnInit() -> bool {

  Logger::setPrefix("client");
  LOG("Starting Battleship Client");

  wxImage::AddHandler(new wxPNGHandler());

  GameWindow *gameWindow = new GameWindow("Battleship", wxDefaultPosition, wxDefaultSize);
  gameWindow->Show(true);
  GameController::init(gameWindow);
  // GameController::showStatus("Not connected");

  return true;
}