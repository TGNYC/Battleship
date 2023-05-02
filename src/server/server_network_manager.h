//
// Created by Tejas Gupta on 4/19/23.
//

#ifndef BATTLESHIP_SERVER_NETWORK_MANAGER_H
#define BATTLESHIP_SERVER_NETWORK_MANAGER_H

#include <functional>
#include <shared_mutex>
#include <thread>
#include <unordered_map>

#include "sockpp/tcp_acceptor.h"
#include "sockpp/tcp_connector.h"
#include "sockpp/tcp_socket.h"

// #include "../common/network/requests/client_request.h"
#include "game_state/Player.h"
#include "network/responses/server_response.h"
// #include "../common/game_state/game_state.h"

class server_network_manager {
private:
  inline static server_network_manager *_instance;
  inline static std::shared_mutex       _rw_lock;
  inline static sockpp::tcp_acceptor    _acc;

  inline static std::unordered_map<uuid, std::string>               _player_id_to_address;
  inline static std::unordered_map<std::string, sockpp::tcp_socket> _address_to_socket;

  void connect(const std::string &url, const uint16_t port);

  static void listener_loop();
  static void
                 read_message(sockpp::tcp_socket                                                                  socket,
                              const std::function<void(const std::string &, const sockpp::tcp_socket::addr_t &)> &message_handler);
  static void    handle_incoming_message(const std::string &msg, const sockpp::tcp_socket::addr_t &peer_address);
  static ssize_t send_message(const std::string &msg, const std::string &address);

public:
  server_network_manager();
  ~server_network_manager();

  // Used to broadcast a server_response (e.g. a full_state_response) to all 'players' except 'exclude'
  static void broadcast_message(server_response &msg, const std::vector<Player *> &players, const Player *exclude);

  static void on_player_left(uuid player_id);
};

#endif // BATTLESHIP_SERVER_NETWORK_MANAGER_H
