#ifndef SENDEMOTE_H
#define SENDEMOTE_H

#include "ClientRequest.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class SendEmote : public ClientRequest {
public:
  explicit SendEmote(const json &jsonMessage);
};

#endif // SENDEMOTE_H