#ifndef PLAYAGAIN_H
#define PLAYAGAIN_H

#include "ClientRequest.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class PlayAgain : public ClientRequest {
public:
  explicit PlayAgain(const json &jsonMessage);
};

#endif // PLAYAGAIN_H