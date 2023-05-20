#include "SendEmote.h"

#include "../../uuid.h"
#include "ClientRequest.h"
#include <string>
#include <utility>

SendEmote::SendEmote(uuid playerId, EmoteType emote)
    : ClientRequest(playerId, RequestType::SendEmote), _emote(emote) {}

//TODO remove
SendEmote::SendEmote(uuid playerId, std::string emote)
: ClientRequest(playerId, RequestType::SendEmote), _emote(EmoteType::MiddleFinger) {}

auto SendEmote::getEmote() const -> EmoteType {
  return _emote;
}