#include "Battleship.h"

#include "GameWindow.h"
#include <memory>

auto Battleship::OnInit() -> bool {
  
  auto* gameWindow = new GameWindow("Battleship", wxDefaultPosition, wxDefaultSize);
  gameWindow->Show(true);

  return true;
}