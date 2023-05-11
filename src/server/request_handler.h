//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_REQUEST_HANDLER_H
#define BATTLESHIP_REQUEST_HANDLER_H

#include "network/requests/ClientRequest.h"
#include "network/responses/ServerResponse.h"
#include <memory>

class request_handler {
public:
  static std::unique_ptr<ServerResponse> handle_request(const ClientRequest *const req);
};

#endif // BATTLESHIP_REQUEST_HANDLER_H
