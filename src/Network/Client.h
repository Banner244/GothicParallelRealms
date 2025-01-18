#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <functional>
#include <unordered_map>

#include "../server/src/Data.h"
#include "../Models/Npc.h"

using boost::asio::ip::udp;

class Client {
public:
    Client(boost::asio::io_context& io_context, const std::string& host, const std::string& port, std::unordered_map<std::string*, Npc*> *clients);

    void send_message(const std::string& message);

    /*void setConnected();
    bool isConnected();*/
    std::unordered_map<std::string*, Npc*> *clients;

private:
    void start_receive();

    

    udp::socket socket_;
    udp::resolver resolver_;
    udp::endpoint server_endpoint_;
    udp::endpoint sender_endpoint_;
    std::array<char, 1024> recv_buffer_;

    bool connected = false;
};