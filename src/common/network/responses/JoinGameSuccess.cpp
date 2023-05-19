//
// Created by robin on 10.05.23.
//

#include "JoinGameSuccess.h"

JoinGameSuccess::JoinGameSuccess() : ServerResponse(ResponseType::JoinGameSuccess) {
  _success = true;
}

bool JoinGameSuccess::wasSuccessful() const {
  return _success;
}