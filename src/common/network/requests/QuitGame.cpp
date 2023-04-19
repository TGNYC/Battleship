#include "QuitGame.h"

#include "../../uuid.h"
#include "ClientRequest.h"

QuitGame::QuitGame(uuid playerId) : ClientRequest(playerId, RequestType::QuitGame) {}