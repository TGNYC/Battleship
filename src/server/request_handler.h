//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_REQUEST_HANDLER_H
#define BATTLESHIP_REQUEST_HANDLER_H

#include "../common/network/requests/ClientRequest.h"
#include "../common/network/responses/server_response.h"
#include "../common/network/responses/request_response.h"

class request_handler {
public:
  static request_response* handle_request(const client_request* const req);
};

#endif // BATTLESHIP_REQUEST_HANDLER_H
