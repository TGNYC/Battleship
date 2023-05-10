#include "SendEmote.h"

#include "../../uuid.h"
#include "ClientRequest.h"
#include <string>
#include <utility>


SendEmote::SendEmote(uuid playerId, EmoteHandler::Emote emote)
    : ClientRequest(playerId, RequestType::SendEmote), m_emote(emote) {}

auto SendEmote::getEmote() const -> EmoteHandler::Emote {
  return m_emote;
}