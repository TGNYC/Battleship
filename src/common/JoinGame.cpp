#include "JoinGame.h"

#include "ClientRequest.h"
#include "uuid.h"
#include <string>
#include <utility>

JoinGame::JoinGame(uuid playerId, std::string playerName)
    : ClientRequest(playerId, RequestType::JoinGame), playerName(std::move(playerName)) {}

auto JoinGame::getPlayerName() const -> std::string {
  return playerName;
}