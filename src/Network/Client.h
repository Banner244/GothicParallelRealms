#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <functional>

#include "../server/src/PackagingSystem.h"
#include "../server/src/Packets.h"

#include "../Logic/GameThreadWorker.h"
#include "../Models/Npc.h"
class GameThreadWorker;

using boost::asio::ip::udp;

class Client {
public:
    Client(boost::asio::io_context& io_context, const std::string& host, const std::string& port, GameThreadWorker *gameThreadWorker);
    ~Client();
    
    void send_message(const std::string &message);

    void sendPlayerPosition();
    void sendPlayerAnimation();
    void sendPlayerRotation();


    /*void setConnected();
    bool isConnected();*/
    Npc * getMainPlayer();

private:
    GameThreadWorker *gameThreadWorker;
    Npc *mainPlayer = new Npc(ADDR_PLAYERBASE);

    udp::socket socket_;
    udp::resolver resolver_;
    udp::endpoint server_endpoint_;
    udp::endpoint sender_endpoint_;
    std::array<char, 1024> recv_buffer_;

    bool connected = false;
    void start_receive();
};