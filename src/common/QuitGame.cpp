#include "QuitGame.h"

#include "ClientRequest.h"
#include "uuid.h"

QuitGame::QuitGame(uuid playerId) : ClientRequest(playerId, RequestType::QuitGame) {}