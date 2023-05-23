#include "SendEmote.h"

#include "../../uuid.h"
#include "ClientRequest.h"
#include <string>
#include <utility>

SendEmote::SendEmote(uuid playerId, EmoteType emote) : ClientRequest(playerId, RequestType::SendEmote), _emote(emote) {}

auto SendEmote::getEmote() const -> EmoteType {
  return _emote;
}