#pragma once

#include <iostream>

#include <boost/asio.hpp>

#include "MessageHandler.h"
#include "CommonStructures.h"

using boost::asio::ip::udp;

class ServerManager {

    public:
        ServerManager(boost::asio::io_context &io_context, boost::asio::io_context &processing_context);
        void watchingHeartbeat();
    private:
        udp::socket socket;
        boost::asio::io_context *processing_context;
        std::unordered_map<std::string, CommonStructures::ClientInfo> clients;

        bool serverRunning = false;

        MessageHandler *messageHandler;
        void start_receive();
        

};