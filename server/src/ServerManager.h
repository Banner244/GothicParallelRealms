#pragma once

#include <iostream>

#include <boost/asio.hpp>

#include "MessageHandler.h"


using boost::asio::ip::udp;

class ServerManager {

    public:
        ServerManager(boost::asio::io_context &io_context, boost::asio::io_context &processing_context);
    private:
        udp::socket socket;
        boost::asio::io_context *processing_context;

        std::unordered_map<std::string, udp::endpoint> clients;

        MessageHandler *messageHandler;
        void start_receive();

};