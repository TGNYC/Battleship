#ifndef JOINGAME_H
#define JOINGAME_H

#include "ClientRequest.h"

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class JoinGame : public ClientRequest {

public:
  explicit JoinGame(const json &jsonMessage);

private:
  std::string playerName;
};

#endif // JOINGAME_H