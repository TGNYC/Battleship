#ifndef SENDEMOTE_H
#define SENDEMOTE_H

#include "ClientRequest.h"
#include <string>
#include "../client/EmoteHandler.h"
class uuid;

class SendEmote : public ClientRequest {
public:
  SendEmote(uuid playerId, EmoteHandler::Emote emote);

  [[nodiscard]] auto getEmote() const -> EmoteHandler::Emote;

  auto operator<=>(const SendEmote &) const = default;

private:
  EmoteHandler::Emote m_emote;
};

#endif // SENDEMOTE_H