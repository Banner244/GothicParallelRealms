#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <functional>

//#include "MessageHandler.h"

//#include "../Models/ImGuiData.h"
#include "../server/src/Data.h"
//#include "../Models/Npc.h"
#include "../Logic/MessageGameThreadManager.h"
class MessageGameThreadManager;

using boost::asio::ip::udp;

class Client {
public:
    Client(boost::asio::io_context& io_context, const std::string& host, const std::string& port, MessageGameThreadManager *gameThreadManager);

    void send_message(const std::string& message);

    /*void setConnected();
    bool isConnected();*/
    MessageGameThreadManager *gameThreadManager;
    //std::unordered_map<std::string, Npc*> *clients;


private:
    void start_receive();

    udp::socket socket_;
    udp::resolver resolver_;
    udp::endpoint server_endpoint_;
    udp::endpoint sender_endpoint_;
    std::array<char, 1024> recv_buffer_;

    bool connected = false;
    //MessageHandler * messageHandler;
    
};