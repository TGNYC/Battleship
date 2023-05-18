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
private:
  inline static std::shared_mutex _rw_lock;
  inline static sockpp::tcp_acceptor _acc;

  inline static std::unordered_map<std::string, sockpp::tcp_socket> _address_to_socket;

  void connect(uint16_t port);
  static ssize_t send_message(const std::string &msg, const std::string &address);
  inline static std::unordered_map<uuid, std::string> _player_id_to_address;

  static void read_message(sockpp::tcp_socket socket,
                    const std::function<void(const std::string &, const sockpp::tcp_socket::addr_t &)> &message_handler);
  void        handle_message(const std::string &msg, const sockpp::tcp_socket::addr_t &peer_address);

  GameInstance _game_instance;
  uint16_t _port;

public:
  ServerNetworkManager(uint16_t port);
  ~ServerNetworkManager();

  // Used to broadcast a server_response (e.g. a full_state_response) to all 'players' except 'exclude'
  static void broadcast_message(ServerResponse &msg, const std::vector<Player> &players, const Player *exclude= nullptr);
  //static void send_message_to_other_server(const std::string &host, const uint16_t port, const std::string &message);
  static void on_player_left(uuid player_id);
  void listener_loop();
};

#endif // BATTLESHIP_SERVERNETWORKMANAGER_H