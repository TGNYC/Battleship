#ifndef CLIENTREQUEST_H
#define CLIENTREQUEST_H

#include "uuid.h"
#include <compare>

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
  [[nodiscard]] auto getRequestType() const -> RequestType;
  [[nodiscard]] auto getPlayerId() const -> uuid;

  auto operator<=>(const ClientRequest &) const = default;

  virtual ~ClientRequest() = default;

protected:
  ClientRequest(uuid playerId, RequestType requestType);

private:
  uuid        m_playerId;
  RequestType m_requestType;
};

#endif // CLIENTREQUEST_H