#include "ErrorResponse.h"

#include <utility>


ErrorResponse::ErrorResponse(BattleshipException exception)
    : ServerResponse(ResponseType::ErrorResponse), exception(std::move(exception)) {}