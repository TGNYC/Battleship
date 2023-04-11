#ifndef CALLSHOT_H
#define CALLSHOT_H

#include "ClientRequest.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CallShot : public ClientRequest {
public:
  explicit CallShot(const json &jsonMessage);
};

#endif // CALLSHOT_H