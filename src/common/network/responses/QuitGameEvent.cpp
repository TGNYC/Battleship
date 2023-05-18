//
// Created by robin on 18.05.23.
//

#include "QuitGameEvent.h"
#include "ServerResponse.h"

QuitGameEvent::QuitGameEvent(uuid quitPlayerId)
    : ServerResponse(ResponseType::QuitGameEvent), quitPlayerId(quitPlayerId) {}