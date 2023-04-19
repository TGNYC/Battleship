#ifndef SERIALIZION_h
#define SERIALIZION_h

#include "CallShot.h"
#include "ClientRequest.h"
#include "Coordinate.h"
#include "JoinGame.h"
#include "PlayAgain.h"
#include "QuitGame.h"
#include "SendEmote.h"
#include "Ship.h"
#include "StartGame.h"
#include <memory>
#include <nlohmann/json.hpp>

inline void to_json(nlohmann::json &json, const Coordinate &position) {
  json["x"] = position.x;
  json["y"] = position.y;
}

inline void from_json(const nlohmann::json &json, Coordinate &position) {
  json.at("x").get_to(position.x);
  json.at("y").get_to(position.y);
}

inline void to_json(nlohmann::json &json, const uuid &uuid) {
  json = uuid.ToString();
}

inline void from_json(const nlohmann::json &json, uuid &uuid_v) {
  uuid_v = uuid(json.get<std::string>());
}

NLOHMANN_JSON_SERIALIZE_ENUM(Ship::Orientation,
                             {{Ship::Orientation::Vertical, "v"}, {Ship::Orientation::Horizontal, "h"}})

NLOHMANN_JSON_SERIALIZE_ENUM(RequestType, {{RequestType::JoinGame, "join_game"},
                                           {RequestType::StartGame, "start_game"},
                                           {RequestType::CallShot, "call_shot"},
                                           {RequestType::SendEmote, "send_emote"},
                                           {RequestType::QuitGame, "quit_game"},
                                           {RequestType::PlayAgain, "play_again"}})

namespace nlohmann {
template <>
struct adl_serializer<Ship> {
  static void to_json(json &json, const Ship &ship) {
    json["ship_id"]     = ship.getId();
    json["length"]      = ship.getLength();
    json["position"]    = ship.getPosition();
    json["orientation"] = ship.getOrientation();
  }
  static auto from_json(const json &json) -> Ship {
    return {json.at("length").get<int>(), json.at("position").get<Coordinate>(),
            json.at("orientation").get<Ship::Orientation>(), json.at("ship_id").get<uuid>()};
  }
};

template <>
struct adl_serializer<ClientRequest> {
  static void to_json(json &json, const ClientRequest &request) {
    json["type"]      = request.getRequestType();
    json["player_id"] = request.getPlayerId();
  }
};

template <>
struct adl_serializer<JoinGame> {
  static void to_json(json &json, const JoinGame &request) {
    json                = static_cast<const ClientRequest &>(request);
    json["player_name"] = request.getPlayerName();
  }
};

template <>
struct adl_serializer<StartGame> {
  static void to_json(json &json, const StartGame &request) {
    json                    = static_cast<const ClientRequest &>(request);
    json["ships_placement"] = request.getShips();
  }
};

template <>
struct adl_serializer<CallShot> {
  static void to_json(json &json, const CallShot &request) {
    json             = static_cast<const ClientRequest &>(request);
    json["position"] = request.getPosition();
  }
};

template <>
struct adl_serializer<SendEmote> {
  static void to_json(json &json, const SendEmote &request) {
    json          = static_cast<const ClientRequest &>(request);
    json["emote"] = request.getEmote();
  }
};

template <>
struct adl_serializer<QuitGame> {
  static void to_json(json &json, const QuitGame &request) {
    json = static_cast<const ClientRequest &>(request);
  }
};

template <>
struct adl_serializer<PlayAgain> {
  static void to_json(json &json, const PlayAgain &request) {
    json = static_cast<const ClientRequest &>(request);
  }
};

template <>
struct adl_serializer<std::unique_ptr<ClientRequest>> {
  static auto from_json(const json &json) -> std::unique_ptr<ClientRequest> {

    const RequestType requestType = json.at("type").get<RequestType>();
    const uuid        playerId    = json.at("player_id").get<uuid>();

    switch (requestType) {
    case RequestType::JoinGame:
      return std::make_unique<JoinGame>(playerId, json.at("player_name").get<std::string>());
    case RequestType::StartGame:
      return std::make_unique<StartGame>(playerId, json.at("ships_placement").get<std::vector<Ship>>());
    case RequestType::CallShot:
      return std::make_unique<CallShot>(playerId, json.at("position").get<Coordinate>());
    case RequestType::SendEmote:
      return std::make_unique<SendEmote>(playerId, json.at("emote").get<std::string>());
    case RequestType::QuitGame:
      return std::make_unique<QuitGame>(playerId);
    case RequestType::PlayAgain:
      return std::make_unique<PlayAgain>(playerId);
    }
    return nullptr;
  }

  static void to_json(json &json, const std::unique_ptr<ClientRequest> &clientRequest) {
    const RequestType requestType = clientRequest->getRequestType();

    switch (requestType) {
    case RequestType::JoinGame:
      json = static_cast<const JoinGame &>(*clientRequest);
      break;
    case RequestType::StartGame:
      json = static_cast<const StartGame &>(*clientRequest);
      break;
    case RequestType::CallShot:
      json = static_cast<const CallShot &>(*clientRequest);
      break;
    case RequestType::SendEmote:
      json = static_cast<const SendEmote &>(*clientRequest);
      break;
    case RequestType::QuitGame:
      json = static_cast<const QuitGame &>(*clientRequest);
      break;
    case RequestType::PlayAgain:
      json = static_cast<const PlayAgain &>(*clientRequest);
      break;
    }
  }
};
} // namespace nlohmann

#endif // SERIALIZION_h