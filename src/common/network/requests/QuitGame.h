#ifndef QUITGAME_H
#define QUITGAME_H

#include "ClientRequest.h"
class uuid;

class QuitGame : public ClientRequest {
public:
  explicit QuitGame(uuid playerId);
};

#endif // QUITGAME_H