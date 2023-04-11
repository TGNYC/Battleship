#ifndef QUITGAME_H
#define QUITGAME_H

#include "ClientRequest.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class QuitGame : public ClientRequest {
public:
  explicit QuitGame(const json &jsonMessage);
};

#endif // QUITGAME_H