#include "SendEmote.h"

#include "../../uuid.h"
#include "ClientRequest.h"
#include <string>
#include <utility>

SendEmote::SendEmote(uuid playerId, EmoteHandler::Emote emote)
    : ClientRequest(playerId, RequestType::SendEmote), m_emote(emote) {}

//TODO remove
SendEmote::SendEmote(uuid playerId, std::string emote)
: ClientRequest(playerId, RequestType::SendEmote), m_emote(EmoteHandler::MiddleFinger) {}

auto SendEmote::getEmote() const -> EmoteHandler::Emote {
  return m_emote;
}