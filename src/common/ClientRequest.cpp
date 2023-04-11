#include "ClientRequest.h"

#include "CallShot.h"
#include "JoinGame.h"
#include "PlayAgain.h"
#include "QuitGame.h"
#include "SendEmote.h"
#include "StartGame.h"
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

auto ClientRequest::fromJson(const json &jsonMessage) -> std::unique_ptr<ClientRequest> {
  const RequestType requestType = jsonMessage.get<RequestType>();
  switch (requestType) {
  case RequestType::JoinGame:
    return std::make_unique<JoinGame>(jsonMessage);
  case RequestType::StartGame:
    return std::make_unique<StartGame>(jsonMessage);
  case RequestType::CallShot:
    return std::make_unique<CallShot>(jsonMessage);
  case RequestType::SendEmote:
    return std::make_unique<SendEmote>(jsonMessage);
  case RequestType::QuitGame:
    return std::make_unique<QuitGame>(jsonMessage);
  case RequestType::PlayAgain:
    return std::make_unique<PlayAgain>(jsonMessage);
  default:
    throw std::invalid_argument("Failed to parse the json message.");
  }
}