#ifndef JOINGAME_H
#define JOINGAME_H

#include "ClientRequest.h"
#include <string>
class uuid;

class JoinGame : public ClientRequest {

public:
  JoinGame(uuid playerId, std::string playerName);

  [[nodiscard]] auto getPlayerName() const -> std::string;

private:
  std::string _playerName;
};

#endif // JOINGAME_H