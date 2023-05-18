#include "game_state/Coordinate.h"
#include "game_state/GameState.h"
#include "game_state/Ship.h"
#include "network/requests/CallShot.h"
#include "network/requests/ClientRequest.h"
#include "network/requests/JoinGame.h"
#include "network/requests/PlayAgain.h"
#include "network/requests/QuitGame.h"
#include "network/requests/SendEmote.h"
#include "network/requests/StartGame.h"
#include "network/responses/EmoteEvent.h"
#include "network/responses/ErrorResponse.h"
#include "network/responses/GameEvent.h"
#include "network/responses/GameOverEvent.h"
#include "network/responses/JoinGameSuccess.h"
#include "network/responses/QuitGameEvent.h"
#include "network/responses/ServerResponse.h"
#include "network/responses/StartGameSuccess.h"
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

  ASSERT_EQ(jsonRequest, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonRequest, request);
}

TEST(responses, EmoteEvent) {
  const std::string jsonString = R"(
{
    "type": "emote_event",
    "player_id": "30981d12-c9ef-4591-9563-868c0134d05c",
    "emote": 2
}
)";

  const nlohmann::json jsonResponse = EmoteEvent(EmoteType::Mocking, uuid("30981d12-c9ef-4591-9563-868c0134d05c"));
  const std::unique_ptr<ServerResponse> request = jsonResponse.get<std::unique_ptr<ServerResponse>>();

  ASSERT_EQ(jsonResponse, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonResponse, request);
}

TEST(responses, ErrorResponse) {
  const std::string jsonString = R"(
{
    "type": "error_response",
    "error_message": "Exception"
}
)";

  const nlohmann::json                  jsonResponse = ErrorResponse(BattleshipException("Exception"));
  const std::unique_ptr<ServerResponse> request      = jsonResponse.get<std::unique_ptr<ServerResponse>>();

  ASSERT_EQ(jsonResponse, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonResponse, request);
}

TEST(responses, GameEvent) {
  const std::string jsonString = R"(
{
    "type": "game_event",
    "player_id": "30981d12-c9ef-4591-9563-868c0134d05c",
    "position": {
        "x": 1,
        "y": 2
    },
    "ship_hit": false,
    "ship_sunk": false,
    "ship": {
        "length": 0,
        "orientation": "h",
        "position": {
            "x": 0,
            "y": 0
        },
        "ship_id": "00000000-0000-0000-0000-000000000000"
    },
    "next_player_id": "00000000-0000-0000-0000-000000000000"
}
)";

  const nlohmann::json jsonResponse = GameEvent(uuid("30981d12-c9ef-4591-9563-868c0134d05c"), {1, 2}, false, false,
                                                Ship(0, {0, 0}, Ship::Orientation::Horizontal, uuid()), uuid());
  const std::unique_ptr<ServerResponse> request = jsonResponse.get<std::unique_ptr<ServerResponse>>();

  ASSERT_EQ(jsonResponse, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonResponse, request);
}

TEST(responses, GameOverEvent) {
  const std::string jsonString = R"(
{
    "type": "game_over_event",
    "winner_player_id": "30981d12-c9ef-4591-9563-868c0134d05c"
}
)";

  const nlohmann::json                  jsonResponse = GameOverEvent(uuid("30981d12-c9ef-4591-9563-868c0134d05c"));
  const std::unique_ptr<ServerResponse> request      = jsonResponse.get<std::unique_ptr<ServerResponse>>();

  ASSERT_EQ(jsonResponse, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonResponse, request);
}

TEST(responses, JoinGameSuccess) {
  const std::string jsonString = R"(
{
    "type": "join_game_success"
}
)";

  const nlohmann::json                  jsonResponse = JoinGameSuccess();
  const std::unique_ptr<ServerResponse> request      = jsonResponse.get<std::unique_ptr<ServerResponse>>();

  ASSERT_EQ(jsonResponse, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonResponse, request);
}

TEST(responses, QuitGameEvent) {
  const std::string jsonString = R"(
{
    "type": "quit_game_event",
    "quit_player_id": "30981d12-c9ef-4591-9563-868c0134d05c"
}
)";

  const nlohmann::json                  jsonResponse = QuitGameEvent(uuid("30981d12-c9ef-4591-9563-868c0134d05c"));
  const std::unique_ptr<ServerResponse> request      = jsonResponse.get<std::unique_ptr<ServerResponse>>();

  ASSERT_EQ(jsonResponse, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonResponse, request);
}

TEST(responses, StartGameSuccess) {
  const std::string jsonString = R"(
{
    "type": "start_game_success",
    "players" : [
        {
            "id" : "00000000-0000-0000-0000-000000000000",
            "name" : "Max"
        },
        {
            "id" : "00000000-0000-0000-0000-000000000000",
            "name" : "Fritz"
        }
    ],
    "starting_player_id" : "30981d12-c9ef-4591-9563-868c0134d05c"
}
)";

  const nlohmann::json jsonResponse =
      StartGameSuccess({Player(uuid(), "Max"), Player(uuid(), "Fritz")}, uuid("30981d12-c9ef-4591-9563-868c0134d05c"));
  const std::unique_ptr<ServerResponse> request = jsonResponse.get<std::unique_ptr<ServerResponse>>();

  ASSERT_EQ(jsonResponse, nlohmann::json::parse(jsonString));
  ASSERT_EQ(jsonResponse, request);
}

TEST(uuid, defautluuid) {
  const uuid uuid;
  ASSERT_EQ(uuid.ToString(), "00000000-0000-0000-0000-000000000000");
}

TEST(uuid, parseuuid) {
  const uuid uuid("a3351d70-2422-45cc-b10e-fb893862094f");
  ASSERT_EQ(uuid.ToString(), "a3351d70-2422-45cc-b10e-fb893862094f");
}


class gameStateTest : public::testing::Test {
protected:
  virtual void SetUp() {
    for (int i = 0; i < 5; ++i) { // fill vector with 5 dummy ships
      shipPlacement.push_back(Ship(3, Coordinate(0,0), Ship::Orientation::Vertical, uuid::generateRandomUuid()));
    }
  }
  GameState         gameState = GameState(GameState::Type::ServerState);
  Player felix = Player(uuid::generateRandomUuid(), "Felix");
  Player malte = Player(uuid::generateRandomUuid(), "Malte");
  std::vector<Ship> shipPlacement;
};

TEST_F(gameStateTest, addPlayer) {
  gameState.addPlayer(felix);
  EXPECT_EQ(gameState.getPlayers().size(), 1);
  gameState.addPlayer(malte);
  ASSERT_EQ(gameState.getPlayers().size(), 2);
  ASSERT_FALSE(gameState.addPlayer(Player(uuid::generateRandomUuid(), "Hermann"))); // already 2 players. full
}

TEST_F(gameStateTest, getPlayer) {
  gameState.addPlayer(felix);
  Player p = gameState.getPlayer(felix.getId());
  ASSERT_EQ(p, felix);
  ASSERT_EQ(p.getId(), felix.getId());
}

TEST_F(gameStateTest, getPlayers) {
  gameState.addPlayer(felix);
  auto players = gameState.getPlayers();
  ASSERT_EQ(players.size(), 1);
  ASSERT_EQ(players[0], felix);
}


TEST_F(gameStateTest, getOtherPlayer) {
  gameState.addPlayer(felix);
  gameState.addPlayer(malte);
  ASSERT_EQ(gameState.getOtherPlayer(malte.getId()).getId(), felix.getId());
  ASSERT_EQ(gameState.getOtherPlayer(felix.getId()).getId(), malte.getId());
}

TEST_F(gameStateTest, addShips) {
  gameState.addPlayer(felix);
  gameState.addPlayer(malte);
  ASSERT_TRUE(gameState.addShips(felix.getId(), shipPlacement));
  ASSERT_FALSE(gameState.addShips(felix.getId(), shipPlacement)); // already have ships of this player
  ASSERT_TRUE(gameState.addShips(malte.getId(), shipPlacement));
}

TEST_F(gameStateTest, registerShot) {
  //TODO
}

TEST_F(gameStateTest, shotIsLegal) {
  gameState.addPlayer(felix);
  gameState.addShips(felix.getId(), shipPlacement);
  Coordinate exceedsGrid (10, 0);
  Coordinate negative (0, -1);
  Coordinate fine (3, 7);
  ASSERT_EQ(gameState.shotIsLegal(felix.getId(), exceedsGrid), false);
  ASSERT_EQ(gameState.shotIsLegal(felix.getId(), negative), false);
  ASSERT_EQ(gameState.shotIsLegal(felix.getId(), fine), true);
}