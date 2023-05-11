#include "SendEmote.h"

#include "../../uuid.h"
#include "ClientRequest.h"
#include <string>
#include <utility>

SendEmote::SendEmote(uuid playerId, EmoteType emote)
    : ClientRequest(playerId, RequestType::SendEmote), m_emote(emote) {}

//TODO remove
SendEmote::SendEmote(uuid playerId, std::string emote)
: ClientRequest(playerId, RequestType::SendEmote), m_emote(EmoteType::MiddleFinger) {}

auto SendEmote::getEmote() const -> EmoteType {
  return m_emote;
}