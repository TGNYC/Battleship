//
// Created by Tejas Gupta on 4/19/23.
//

//
// Created by manuel on 17.03.21.
//

#include "server_network_manager.h"
#include "Logger.h"

int main() {
  Logger::log("Starting Battleship Server", Logger::Type::Info);
  // create server_network_manager, which listens endlessly for new connections
  server_network_manager server;
  return 0;
}