#ifndef BATTLESHIP_EMOTEEVENT_H
#define BATTLESHIP_EMOTEEVENT_H

#include "game_state/Player.h"
#include "network/responses/ServerResponse.h"
#include <array>

enum class EmoteType {
  Emote1,
  Emote2
};

class EmoteEvent : public ServerResponse {
public:
  const EmoteType emote;
  const uuid      playerId;

  EmoteEvent(EmoteType emote, uuid playerId);
};

#endif // BATTLESHIP_EMOTEEVENT_H