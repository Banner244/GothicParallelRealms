#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <functional>

#include "../common/src/Network/PackagingSystem.h"
#include "../common/src/Network/Packets.h"

#include "../Logic/GameThreadWorker.h"
#include "../Models/Npc.h"
class GameThreadWorker;

using boost::asio::ip::udp;

/**
 * @class Client
 * @brief Manages the network connection between the game client and the server.
 *
 * The Client class is responsible for sending and receiving data over a UDP connection.
 * It interacts with the game logic to synchronize player position, animation, and rotation.
 */
class Client
{
public:
    /**
     * @brief Constructs a Client object and initializes the network connection.
     * @param io_context Boost.Asio IO context for managing asynchronous operations.
     * @param host The server hostname or IP address.
     * @param port The server port number.
     * @param gameThreadWorker Pointer to the game thread worker for processing game-related tasks.
     */
    Client(boost::asio::io_context &io_context, const std::string &username, const std::string &host, const std::string &port, GameThreadWorker *gameThreadWorker);
    ~Client();

    void send_message(const std::string &message);


    void sendHandshakeRequest();
    void sendPlayerPosition();
    void sendPlayerAnimation();
    void sendPlayerRotation();

    Npc *getMainPlayer();

    void setConnected();
    const bool isConnected() const;

private:
    GameThreadWorker *gameThreadWorker;
    Npc *mainPlayer = new Npc(ADDR_PLAYERBASE);
    std::string username;
    udp::socket socket_;
    udp::resolver resolver_;
    udp::endpoint server_endpoint_;
    udp::endpoint sender_endpoint_;
    std::array<char, 1024> recv_buffer_;

    bool connected = false;
    void start_receive();
};