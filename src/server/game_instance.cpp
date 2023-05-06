//
// Created by Tejas Gupta on 4/19/23.
//

#include "game_instance.h"

bool game_instance::executeShot(CallShot shotRequest) {

  if (!_game_state->shotIsLegal(shotRequest.getPlayerId(), shotRequest.getPosition())) {
    // TODO emit error response
    return false;
  }

  // variables to be determined by game_state
  bool hit; // indicates if the shot was a hit
  Ship *hitShip; // the ship that was hit (if there was a hit)
  bool sunk;  // indicates if a ship was sunk
  uuid nextPlayerId;  // player who goes next

  // register shot and get results
  _game_state->registerShot(shotRequest.getPlayerId(), shotRequest.getPosition(),
                            &hit, &hitShip, &sunk, &nextPlayerId);
  // TODO send gameEvent response to clients with this information

  if (_game_state->gameOver()) {
    uuid winnerId = _game_state->getWinner();
    // TODO send GameOver response to clients
  }
}