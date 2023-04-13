#include "SendEmote.h"

#include "ClientRequest.h"
#include "uuid.h"
#include <string>
#include <utility>

SendEmote::SendEmote(uuid playerId, std::string emote)
    : ClientRequest(playerId, RequestType::SendEmote), m_emote(std::move(emote)) {}

auto SendEmote::getEmote() const -> std::string {
  return m_emote;
}