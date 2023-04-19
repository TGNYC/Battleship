#include "Battleship.h"

#include "GameWindow.h"
#include <memory>

auto Battleship::OnInit() -> bool {
  
  std::unique_ptr<GameWindow> gameWindow = std::make_unique<GameWindow>("Battleship", wxDefaultPosition, wxDefaultSize);
  gameWindow->Show(true);

  return true;
}