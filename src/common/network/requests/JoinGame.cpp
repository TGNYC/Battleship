#include "JoinGame.h"

#include "../../uuid.h"
#include "ClientRequest.h"
#include <string>
#include <utility>

JoinGame::JoinGame(uuid playerId, std::string playerName)
    : ClientRequest(playerId, RequestType::JoinGame), _playerName(std::move(playerName)) {}

auto JoinGame::getPlayerName() const -> std::string {
  return _playerName;
}