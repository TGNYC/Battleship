#include "game_state/Coordinate.h"
#include "game_state/Ship.h"
#include "network/requests/CallShot.h"
#include "network/requests/ClientRequest.h"
#include "network/requests/JoinGame.h"
#include "network/requests/PlayAgain.h"
#include "network/requests/QuitGame.h"
#include "network/requests/SendEmote.h"
#include "network/requests/StartGame.h"
#include "serialization/serialization.h" // IWYU pragma: keep
#include "uuid.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

TEST(requests, CallShot) {
  const std::string jsonString = R"(
{
    "type": "call_shot",
    "player_id": "30981d12-c9ef-4591-9563-868c0134d05c",
    "position": {
        "x": 5,
        "y": 3
    }
}
)";

  const nlohmann::json                 jsonRequest = CallShot(uuid("30981d12-c9ef-4591-9563-868c0134d05c"), {5, 3});
  const std::unique_ptr<ClientRequest> request     = jsonRequest.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(jsonRequest, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonRequest, request);
}

TEST(requests, JoinGame) {
  const std::string jsonString = R"(
{
    "type": "join_game",
    "player_id": "30981d12-c9ef-4591-9563-868c0134d05c",
    "player_name": "Max"
}
)";

  const nlohmann::json                 jsonRequest = JoinGame(uuid("30981d12-c9ef-4591-9563-868c0134d05c"), "Max");
  const std::unique_ptr<ClientRequest> request     = jsonRequest.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(jsonRequest, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonRequest, request);
}

TEST(requests, PlayAgain) {
  const std::string jsonString = R"(
{
    "type": "play_again",
    "player_id": "30981d12-c9ef-4591-9563-868c0134d05c"
}
)";

  const nlohmann::json                 jsonRequest = PlayAgain(uuid("30981d12-c9ef-4591-9563-868c0134d05c"));
  const std::unique_ptr<ClientRequest> request     = jsonRequest.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(jsonRequest, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonRequest, request);
}

TEST(requests, QuitGame) {
  const std::string jsonString = R"(
{
    "type": "quit_game",
    "player_id": "30981d12-c9ef-4591-9563-868c0134d05c"
}
)";

  const nlohmann::json                 jsonRequest = QuitGame(uuid("30981d12-c9ef-4591-9563-868c0134d05c"));
  const std::unique_ptr<ClientRequest> request     = jsonRequest.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(jsonRequest, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonRequest, request);
}

TEST(requests, SendEmote) {
  const std::string jsonString = R"(
{
    "type": "send_emote",
    "player_id": "30981d12-c9ef-4591-9563-868c0134d05c",
    "emote": 2
}
)";

  const nlohmann::json jsonRequest = SendEmote(uuid("30981d12-c9ef-4591-9563-868c0134d05c"), EmoteType::Mocking);
  const std::unique_ptr<ClientRequest> request = jsonRequest.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(jsonRequest, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonRequest, request);
}

TEST(requests, StartGame) {
  const std::string jsonString = R"(
{
    "type": "start_game",
    "player_id": "30981d12-c9ef-4591-9563-868c0134d05c",
    "ships_placement": [
        {
            "ship_id": "00000000-0000-0000-0000-000000000000",
            "length": 2,
            "position": {
                "x": 6,
                "y": 5
            },
            "orientation": "h"
        },
        {
            "ship_id": "00000000-0000-0000-0000-000000000000",
            "length": 5,
            "position": {
                "x": 1,
                "y": 3
            },
            "orientation": "v"
        }
    ]
}
)";

  const nlohmann::json jsonRequest =
      StartGame(uuid("30981d12-c9ef-4591-9563-868c0134d05c"),
                {{2, {6, 5}, Ship::Orientation::Horizontal, uuid()}, {5, {1, 3}, Ship::Orientation::Vertical, uuid()}});
  const std::unique_ptr<ClientRequest> request = jsonRequest.get<std::unique_ptr<ClientRequest>>();

  std::cout << jsonRequest.dump(4) << '\n';

  ASSERT_EQ(jsonRequest, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonRequest, request);
}

TEST(uuid, defautluuid) {
  const uuid uuid;
  ASSERT_EQ(uuid.ToString(), "00000000-0000-0000-0000-000000000000");
}

TEST(uuid, parseuuid) {
  const uuid uuid("a3351d70-2422-45cc-b10e-fb893862094f");
  ASSERT_EQ(uuid.ToString(), "a3351d70-2422-45cc-b10e-fb893862094f");
}