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
  bool hit;
  Ship *hitShip;
  bool sunk;
  uuid nextPlayerId;
  // register shot and get results
  _game_state->registerShot(shotRequest.getPlayerId(), shotRequest.getPosition(),
                            &hit, &hitShip, &sunk, &nextPlayerId);
  // TODO send gameEvent response to clients with this information
  uuid winner;
  if (_game_state->gameOver(&winner)) {
    // TODO send GameOver response to clients
  }
}