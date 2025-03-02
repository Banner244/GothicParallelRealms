#pragma once

#include <iostream>

#include <boost/asio.hpp>

//#include "Data.h"
#include "Packets.h"
#include "PackagingSystem.h"
#include "CommonStructures.h"
#include "ServerManager.h"

using boost::asio::ip::udp;

class ServerManager;

class MessageHandler
{

public:
    MessageHandler(ServerManager &serverManager, std::unordered_map<std::string, CommonStructures::ClientInfo> &clients, udp::socket &socket);
    void handleBuffer(udp::endpoint &clientEndpoint, std::string buffer);


private:
    std::unordered_map<std::string, CommonStructures::ClientInfo> *clients;
    udp::socket * pSocket;
    

    ServerManager *pServerManager;

    void clientRepondsHeartbeat(udp::endpoint &clientEndpoint, std::string &buffer);
    void clientSharesPosition(udp::endpoint &clientEndpoint, std::string &buffer);
    void clientSharesAnimations(udp::endpoint &clientEndpoint, std::string &buffer);


};