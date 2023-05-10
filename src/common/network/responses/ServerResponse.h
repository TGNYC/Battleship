//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_SERVERRESPONSE_H
#define BATTLESHIP_SERVERRESPONSE_H

#include <compare>

enum class ResponseType {
  GameEvent,
  EmoteEvent,
  JoinGameSuccess,
  ErrorResponse
};

class ServerResponse {
public:
  const ResponseType responseType;

  auto operator<=>(const ServerResponse &) const = default;

protected:
  explicit ServerResponse(ResponseType responseType);
};

#endif // BATTLESHIP_SERVERRESPONSE_H
