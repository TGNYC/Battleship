//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_REQUEST_HANDLER_H
#define BATTLESHIP_REQUEST_HANDLER_H

// TODO: Look for server, client, and request_response in common
//#include "../common/network/responses/server_response.h"
//#include "../common/network/requests/client_request.h"
//#include "../common/network/responses/request_response.h"

class request_handler {
public:
  static request_response* handle_request(const client_request* const req);
};

#endif // BATTLESHIP_REQUEST_HANDLER_H
