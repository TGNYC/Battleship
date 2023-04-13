#ifndef SENDEMOTE_H
#define SENDEMOTE_H

#include "ClientRequest.h"
#include <string>
class uuid;

class SendEmote : public ClientRequest {
public:
  SendEmote(uuid playerId, std::string emote);

  [[nodiscard]] auto getEmote() const -> std::string;

  auto operator<=>(const SendEmote &) const = default;

private:
  std::string m_emote;
};

#endif // SENDEMOTE_H