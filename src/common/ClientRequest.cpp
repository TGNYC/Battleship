#include "ClientRequest.h"

#include "uuid.h"

auto ClientRequest::getRequestType() const -> RequestType {
  return m_requestType;
}

auto ClientRequest::getPlayerId() const -> uuid {
  return m_playerId;
}

ClientRequest::ClientRequest(uuid playerId, RequestType requestType)
    : m_playerId(playerId), m_requestType(requestType) {}
