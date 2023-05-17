#include "GameOverEvent.h"

#include "uuid.h"

GameOverEvent::GameOverEvent(uuid winnerPlayerId)
    : ServerResponse(ResponseType::GameOverEvent), winnerPlayerId(winnerPlayerId) {}