//
// Created by robin on 10.05.23.
//

#ifndef BATTLESHIP_JOINGAMESUCCESS_H
#define BATTLESHIP_JOINGAMESUCCESS_H

#include "network/responses/ServerResponse.h"

#include "network/responses/ServerResponse.h"
#include "uuid.h"
#include "network/requests/ClientRequest.h"

/*!
 * ServerResponse to a ClientRequest of whether it was successful or not
 */
class JoinGameSuccess : public ServerResponse {
public:
  JoinGameSuccess(uuid playerId);
};

#endif // BATTLESHIP_JOINGAMESUCCESS_H
