#ifndef JOINGAME_H
#define JOINGAME_H

#include "ClientRequest.h"
#include <string>
class uuid;

class JoinGame : public ClientRequest {

public:
  JoinGame(uuid playerId, std::string playerName);

  auto getPlayerName() const -> std::string;

  auto operator<=>(const JoinGame &) const = default;

private:
  std::string m_playerName;
};

#endif // JOINGAME_H