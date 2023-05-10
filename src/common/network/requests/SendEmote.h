#ifndef SENDEMOTE_H
#define SENDEMOTE_H

#include "../../../client/EmoteHandler.h"
#include "ClientRequest.h"
#include <string>

class uuid;
class EmoteHandler;

class SendEmote : public ClientRequest {
public:
  SendEmote(uuid playerId, EmoteHandler::Emote emote);
  SendEmote(uuid playerId, std::string emote); //TODO remove this. just keeping it until serialization uses the other constructor

  [[nodiscard]] auto getEmote() const -> EmoteHandler::Emote;

  auto operator<=>(const SendEmote &) const = default;

private:
  EmoteHandler::Emote m_emote;
};

#endif // SENDEMOTE_H