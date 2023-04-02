#include "Battleship.h"

#include "GameWindow.h"

bool Battleship::OnInit() {
  GameWindow *gameWindow =
      new GameWindow("Battleship", wxDefaultPosition, wxDefaultSize);
  gameWindow->Show(true);

  return true;
}