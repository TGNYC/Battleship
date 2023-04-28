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

TEST(serialization, JoinGame) {

  const JoinGame joinGameRequest(uuid::generateRandomUuid(), "Bob");

  const nlohmann::json message = joinGameRequest;

  const auto clientRequest = message.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(joinGameRequest,
            static_cast<const JoinGame &>(*clientRequest)); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
}

TEST(serialization, StartGame) {

  std::vector<Ship> ships;
  ships.emplace_back(2, Coordinate{5, 2}, Ship::Orientation::Vertical, uuid::generateRandomUuid());
  ships.emplace_back(4, Coordinate{0, 6}, Ship::Orientation::Horizontal, uuid::generateRandomUuid());

  const StartGame startGameRequest(uuid::generateRandomUuid(), ships);

  const nlohmann::json message = startGameRequest;

  const auto clientRequest = message.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(startGameRequest,
            static_cast<const StartGame &>(*clientRequest)); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
}

TEST(serialization, CallShot) {

  const CallShot callShotRequest(uuid::generateRandomUuid(), Coordinate{3, 6});

  const nlohmann::json message = callShotRequest;

  const auto clientRequest = message.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(callShotRequest,
            static_cast<const CallShot &>(*clientRequest)); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
}

TEST(serialization, SendEmote) {

  const SendEmote sendEmoteRequest(uuid::generateRandomUuid(), "🚢");

  const nlohmann::json message = sendEmoteRequest;

  const auto clientRequest = message.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(sendEmoteRequest,
            static_cast<const SendEmote &>(*clientRequest)); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
}

TEST(serialization, QuitGame) {

  const QuitGame quitGameRequest(uuid::generateRandomUuid());

  const nlohmann::json message = quitGameRequest;

  const auto clientRequest = message.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(quitGameRequest,
            static_cast<const QuitGame &>(*clientRequest)); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
}

TEST(serialization, PlayAgain) {

  const PlayAgain playAgainRequest(uuid::generateRandomUuid());

  const nlohmann::json message = playAgainRequest;

  const auto clientRequest = message.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(playAgainRequest,
            static_cast<const PlayAgain &>(*clientRequest)); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
}

TEST(uuid, defautluuid) {
  const uuid uuid;
  ASSERT_EQ(uuid.ToString(), "00000000-0000-0000-0000-000000000000");
}

TEST(uuid, parseuuid) {
  const uuid uuid("a3351d70-2422-45cc-b10e-fb893862094f");
  ASSERT_EQ(uuid.ToString(), "a3351d70-2422-45cc-b10e-fb893862094f");
}