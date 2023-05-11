#ifndef SENDEMOTE_H
#define SENDEMOTE_H

#include "network/responses/EmoteEvent.h"
#include "ClientRequest.h"
#include <string>

class uuid;
class EmoteHandler;

class SendEmote : public ClientRequest {
public:
  SendEmote(uuid playerId, EmoteType emote);
  SendEmote(uuid playerId, std::string emote); //TODO remove this. just keeping it until serialization uses the other constructor

  [[nodiscard]] auto getEmote() const -> EmoteType;

  auto operator<=>(const SendEmote &) const = default;

private:
  EmoteType m_emote;
};

#endif // SENDEMOTE_H