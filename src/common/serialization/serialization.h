#ifndef SERIALIZION_h
#define SERIALIZION_h

#include "game_state/Coordinate.h"
#include "game_state/Ship.h"
#include "network/requests/CallShot.h"
#include "network/requests/ClientRequest.h"
#include "network/requests/JoinGame.h"
#include "network/requests/PlayAgain.h"
#include "network/requests/QuitGame.h"
#include "network/requests/SendEmote.h"
#include "network/requests/StartGame.h"
#include "network/responses/ErrorResponse.h"
#include "network/responses/GameEvent.h"
#include "network/responses/ServerResponse.h"
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

NLOHMANN_JSON_SERIALIZE_ENUM(ResponseType, {{ResponseType::GameEvent, "game_event"},
                                            {ResponseType::EmoteEvent, "emote_event"},
                                            {ResponseType::ErrorResponse, "error_response"}})

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
      return std::make_unique<SendEmote>(playerId, json.at("emote").get<std::string>());  // TODO serialize this with Emote enum instead of string
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

template <>
struct adl_serializer<ServerResponse> {
  static void to_json(json &json, const ServerResponse &responses) {
    json["type"] = responses.responseType;
  }
};

template <>
struct adl_serializer<GameEvent> {
  static void to_json(json &json, const GameEvent &responses) {
    json                   = static_cast<const ServerResponse &>(responses);
    json["player_id"]      = responses.playerId;
    json["position"]       = responses.position;
    json["ship_hit"]       = responses.hit;
    json["ship_sunk"]      = responses.sunk;
    json["ship"]           = responses.hitShip;
    json["next_player_id"] = responses.nextPlayerId;
  }
};

template <>
struct adl_serializer<ErrorResponse> {
  static void to_json(json &json, const ErrorResponse &responses) {
    json                  = static_cast<const ServerResponse &>(responses);
    json["error_message"] = responses.exception.what();
  }
};

template <>
struct adl_serializer<std::unique_ptr<ServerResponse>> {
  static auto from_json(const json &json) -> std::unique_ptr<ServerResponse> {

    const ResponseType responseType = json.at("type").get<ResponseType>();

    switch (responseType) {
    case ResponseType::GameEvent:
      return std::make_unique<GameEvent>(json.at("player_id").get<uuid>(), json.at("position").get<Coordinate>(),
                                         json.at("ship_hit").get<bool>(), json.at("ship_sunk").get<bool>(),
                                         json.at("ship").get<Ship>(), json.at("next_player_id").get<uuid>());
    case ResponseType::EmoteEvent:
      return nullptr;
    case ResponseType::ErrorResponse:
      return std::make_unique<ErrorResponse>(BattleshipException(json.at("error_message").get<std::string>()));
    }
    return nullptr;
  }

  static void to_json(json &json, const std::unique_ptr<ServerResponse> &serverResponse) {
    const ResponseType responsesType = serverResponse->responseType;

    switch (responsesType) {
    case ResponseType::GameEvent:
      json = static_cast<const GameEvent &>(*serverResponse);
      break;
    case ResponseType::EmoteEvent:
      // TODO create class EmoteEvent
      // json = static_cast<const EmoteEvent &>(*serverResponse);
      break;
    case ResponseType::ErrorResponse:
      json = static_cast<const ErrorResponse &>(*serverResponse);
      break;
    }
  }
};

} // namespace nlohmann

#endif // SERIALIZION_h