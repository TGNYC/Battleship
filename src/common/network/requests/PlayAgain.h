#ifndef PLAYAGAIN_H
#define PLAYAGAIN_H

#include "ClientRequest.h"
class uuid;

class PlayAgain : public ClientRequest {
public:
  explicit PlayAgain(uuid playerId);
};

#endif // PLAYAGAIN_H