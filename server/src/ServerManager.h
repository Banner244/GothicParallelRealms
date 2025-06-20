#pragma once

#include <iostream>

#include <boost/asio.hpp>

#include "MessageHandler.h"
#include "CommonStructures.h"

#include "Monitoring/MonitoringClient.h"

#include "../../common/src/Async/AsyncUnorderedMap.h"
#include "../../common/src/IniManager.h"
using boost::asio::ip::udp;

class ServerManager {

    public:
        ServerManager(boost::asio::io_context &io_context, boost::asio::io_context &processing_context, CommonStructures::Ini configData);
        void watchingHeartbeat();
    private:
        udp::socket socket;
        boost::asio::io_context *processing_context;
        AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> clients;

        bool serverRunning = false;

        MessageHandler *messageHandler;
        void start_receive();

        CommonStructures::Ini configData;
        std::unique_ptr<MonitoringClient> monitor;

};