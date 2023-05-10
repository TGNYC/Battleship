#ifndef BATTLESHIP_ERRORRESPONSE_H
#define BATTLESHIP_ERRORRESPONSE_H

#include "exceptions/BattleshipException.h"
#include "network/responses/ServerResponse.h"

class ErrorResponse : public ServerResponse {
public:
  const BattleshipException exception;

  explicit ErrorResponse(BattleshipException exception);
};

#endif // BATTLESHIP_ERRORRESPONSE_H