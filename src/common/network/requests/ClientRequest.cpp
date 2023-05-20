#include "ClientRequest.h"

#include "uuid.h"

auto ClientRequest::getRequestType() const -> RequestType {
  return _requestType;
}

auto ClientRequest::getPlayerId() const -> uuid {
  return _playerId;
}

ClientRequest::ClientRequest(uuid playerId, RequestType requestType)
    : _playerId(playerId), _requestType(requestType) {}
