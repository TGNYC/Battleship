#include "PlayAgain.h"

#include "ClientRequest.h"
#include "uuid.h"

PlayAgain::PlayAgain(uuid playerId) : ClientRequest(playerId, RequestType::PlayAgain) {}