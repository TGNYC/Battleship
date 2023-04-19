#include "PlayAgain.h"

#include "../../uuid.h"
#include "ClientRequest.h"

PlayAgain::PlayAgain(uuid playerId) : ClientRequest(playerId, RequestType::PlayAgain) {}