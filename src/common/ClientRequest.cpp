#include "ClientRequest.h"

#include "uuid.h"

auto ClientRequest::getRequestType() const -> RequestType {
  return requestType;
}

auto ClientRequest::getPlayerId() const -> uuid {
  return playerId;
}

ClientRequest::ClientRequest(uuid playerId, RequestType requestType) : playerId(playerId), requestType(requestType){};
