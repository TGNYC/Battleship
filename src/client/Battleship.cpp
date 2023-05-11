#include "Battleship.h"

#include "GameWindow.h"
#include <memory>
#include "panels/ConnectionPanel.h"
#include "panels/SetupPanel.h"
#include "GameController.h"
#include "Logger.h"

auto Battleship::OnInit() -> bool {

  Logger::log("Starting Battleship Client", Logger::Type::Info);

  wxImage::AddHandler(new wxPNGHandler());

  GameWindow *gameWindow = new GameWindow("Battleship", wxDefaultPosition, wxDefaultSize);
  gameWindow->Show(true);
  GameController::init(gameWindow);
  // GameController::showStatus("Not connected");

  return true;
}