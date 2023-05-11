#include "EmoteEvent.h"

EmoteEvent::EmoteEvent(EmoteType emote, uuid playerId)
    : ServerResponse(ResponseType::EmoteEvent), emote(emote), playerId(playerId) {}