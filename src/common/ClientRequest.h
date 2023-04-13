#ifndef CLIENTREQUEST_H
#define CLIENTREQUEST_H

#include "uuid.h"

enum class RequestType {
  JoinGame,
  StartGame,
  CallShot,
  SendEmote,
  QuitGame,
  PlayAgain
};

class ClientRequest {
public:
  auto getRequestType() const -> RequestType;
  auto getPlayerId() const -> uuid;

  auto operator<=>(const ClientRequest &) const = default;

protected:
  ClientRequest(uuid playerId, RequestType requestType);

private:
  uuid        m_playerId;
  RequestType m_requestType;
};

#endif // CLIENTREQUEST_H