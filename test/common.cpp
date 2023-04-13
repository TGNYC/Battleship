#include "CallShot.h"
#include "ClientRequest.h"
#include "Coordinate.h"
#include "JoinGame.h"
#include "PlayAgain.h"
#include "QuitGame.h"
#include "SendEmote.h"
#include "Ship.h"
#include "StartGame.h"
#include "serialization.h" // IWYU pragma: keep
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

  ASSERT_EQ(joinGameRequest, static_cast<const JoinGame &>(*clientRequest));
}

TEST(serialization, StartGame) {

  std::vector<Ship> ships;
  ships.emplace_back(2, Coordinate{5, 2}, Ship::Orientation::Vertical, uuid::generateRandomUuid());
  ships.emplace_back(4, Coordinate{0, 6}, Ship::Orientation::Horizontal, uuid::generateRandomUuid());

  const StartGame startGameRequest(uuid::generateRandomUuid(), ships);

  const nlohmann::json message = startGameRequest;

  const auto clientRequest = message.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(startGameRequest, static_cast<const StartGame &>(*clientRequest));
}

TEST(serialization, CallShot) {

  const CallShot callShotRequest(uuid::generateRandomUuid(), Coordinate{3, 6});

  nlohmann::json message = callShotRequest;

  const auto clientRequest = message.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(callShotRequest, static_cast<const CallShot &>(*clientRequest));
}

TEST(serialization, SendEmote) {

  const SendEmote sendEmoteRequest(uuid::generateRandomUuid(), "🚢");

  nlohmann::json message = sendEmoteRequest;

  const auto clientRequest = message.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(sendEmoteRequest, static_cast<const SendEmote &>(*clientRequest));
}

TEST(serialization, QuitGame) {

  const QuitGame quitGameRequest(uuid::generateRandomUuid());

  nlohmann::json message = quitGameRequest;

  const auto clientRequest = message.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(quitGameRequest, static_cast<const QuitGame &>(*clientRequest));
}

TEST(serialization, PlayAgain) {

  const PlayAgain playAgainRequest(uuid::generateRandomUuid());

  const nlohmann::json message = playAgainRequest;

  const auto clientRequest = message.get<std::unique_ptr<ClientRequest>>();

  ASSERT_EQ(playAgainRequest, static_cast<const PlayAgain &>(*clientRequest));
}

TEST(uuid, defautluuid) {
  const uuid uuid;
  ASSERT_EQ(uuid.ToString(), "00000000-0000-0000-0000-000000000000");
}

TEST(uuid, parseuuid) {
  const uuid uuid("a3351d70-2422-45cc-b10e-fb893862094f");
  ASSERT_EQ(uuid.ToString(), "a3351d70-2422-45cc-b10e-fb893862094f");
}