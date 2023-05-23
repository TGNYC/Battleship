#ifndef SENDEMOTE_H
#define SENDEMOTE_H

#include "ClientRequest.h"
#include "network/responses/EmoteEvent.h"
#include <string>

class uuid;
class EmoteHandler;

class SendEmote : public ClientRequest {
public:
  SendEmote(uuid playerId, EmoteType emote);

  [[nodiscard]] auto getEmote() const -> EmoteType;

private:
  EmoteType _emote;
};

#endif // SENDEMOTE_H