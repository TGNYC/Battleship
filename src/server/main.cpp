//
// Created by Tejas Gupta on 4/19/23.
//

#include "Logger.h"
#include "ServerNetworkManager.h"

int main() {
  Logger::setPrefix("server");
  LOG("Starting Battleship Server");
  // create server_network_manager, which listens endlessly for new connections
  ServerNetworkManager server(8080);
  server.listenerLoop();
  return 0;
}