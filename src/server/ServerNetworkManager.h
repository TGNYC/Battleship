//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_SERVERNETWORKMANAGER_H
#define BATTLESHIP_SERVERNETWORKMANAGER_H

#include "GameInstance.h"
#include "game_state/Player.h"
#include "network/responses/ServerResponse.h"
#include "sockpp/tcp_acceptor.h"
#include "sockpp/tcp_connector.h"
#include "sockpp/tcp_socket.h"
#include <functional>
#include <shared_mutex>
#include <thread>
#include <unordered_map>

class ServerNetworkManager {
public:

  ServerNetworkManager(uint16_t port);
  ~ServerNetworkManager();
  // Used to broadcast a server_response (e.g. a full_state_response) to all 'players' except 'exclude'
  static void broadcastMessage(ServerResponse &msg, const std::vector<Player> &players, const Player *exclude= nullptr);
  static void on_player_left(uuid player_id);

  void listenerLoop();

private:
  inline static std::shared_mutex    _rwLock;
  inline static sockpp::tcp_acceptor _acc;
  inline static std::unordered_map<std::string, sockpp::tcp_socket> _addressToSocket;
  inline static std::unordered_map<uuid, std::string> _playerIdToAddress;

  static ssize_t sendMessage(const std::string &msg, const std::string &address);
  static void readMessage(sockpp::tcp_socket socket,
                          const std::function<void(const std::string &, const sockpp::tcp_socket::addr_t &)> &message_handler);

  void connect(uint16_t port);
  void handleMessage(const std::string &msg, const sockpp::tcp_socket::addr_t &peer_address);

  GameInstance _gameInstance;
  uint16_t _port;
};

#endif // BATTLESHIP_SERVERNETWORKMANAGER_H
