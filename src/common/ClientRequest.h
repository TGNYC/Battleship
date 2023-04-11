#ifndef CLIENTREQUEST_H
#define CLIENTREQUEST_H

#include <memory>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

enum class RequestType {
  JoinGame,
  StartGame,
  CallShot,
  SendEmote,
  QuitGame,
  PlayAgain
};

class ClientRequest {
public:
  auto        getRequestType() -> RequestType;
  static auto fromJson(const json &message) -> std::unique_ptr<ClientRequest>;

protected:
  ClientRequest(std::string playerId, RequestType requestType);

private:
  std::string playerId;
  RequestType requestType;
};

#endif // CLIENTREQUEST_H