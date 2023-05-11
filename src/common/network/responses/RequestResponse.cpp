//
// Created by Tejas Gupta on 5/10/23.
//

#include "RequestResponse.h"

RequestResponse::RequestResponse(uuid playerId, bool success, RequestType requestType)
    : ServerResponse(ResponseType::RequestResponse) {}