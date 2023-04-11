#ifndef STARTGAME_H
#define STARTGAME_H

#include "ClientRequest.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class StartGame : public ClientRequest {
public:
  explicit StartGame(const json &jsonMessage);
};

#endif // STARTGAME_H