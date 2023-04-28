#include "Battleship.h"

#include "GameWindow.h"
#include <memory>
#include "panels/ConnectionPanel.h"
#include "panels/SetupPanel.h"

auto Battleship::OnInit() -> bool {

  wxImage::AddHandler(new wxPNGHandler());

  auto* gameWindow = new GameWindow("Battleship", wxDefaultPosition, wxDefaultSize);
  gameWindow->Show(true);

  // GameController::init(gameWindow);
  // test
  //auto connectionPanel = new ConnectionPanel(gameWindow);
  //connectionPanel->Show(false);
  //gameWindow->showPanel(connectionPanel);

  auto setupPanel = new SetupPanel(gameWindow);
  setupPanel->Show(false);
  gameWindow->showPanel(setupPanel);
  // GameController::showStatus("Not connected");

  return true;
}