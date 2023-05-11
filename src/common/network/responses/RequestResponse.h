//
// Created by Tejas Gupta on 5/10/23.
//

#ifndef BATTLESHIP_REQUESTRESPONSE_H
#define BATTLESHIP_REQUESTRESPONSE_H

#include "network/responses/ServerResponse.h"
#include "uuid.h"
#include "network/requests/ClientRequest.h"

/*!
 * ServerResponse to a ClientRequest of whether it was successful or not
 */
class RequestResponse : public ServerResponse {
public:
  RequestResponse(uuid playerId, bool success, RequestType requestType);
};

#endif // BATTLESHIP_REQUESTRESPONSE_H

