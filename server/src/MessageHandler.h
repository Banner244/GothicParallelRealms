#pragma once

#include <iostream>

#include <boost/asio.hpp>

//#include "Data.h"
#include "Packets.h"
#include "PackagingSystem.h"
#include "CommonStructures.h"


using boost::asio::ip::udp;

class MessageHandler
{

public:
    MessageHandler(std::unordered_map<std::string, CommonStructures::ClientInfo> &clients, udp::socket &socket);
    void handleBuffer(udp::endpoint &clientEndpoint, std::string buffer);

    void removeClient(udp::endpoint &clientEndpoint);

    void sendMessage(udp::endpoint &clientEndpoint, std::string buffer);
private:
    std::unordered_map<std::string, CommonStructures::ClientInfo> *clients;
    udp::socket * pSocket;
    std::mutex clients_mutex;

    void clientRepondsHeartbeat(udp::endpoint &clientEndpoint, std::string &buffer);
    void clientSharesPosition(udp::endpoint &clientEndpoint, std::string &buffer);
    void clientSharesAnimations(udp::endpoint &clientEndpoint, std::string &buffer);

    


    void addNewClient(udp::endpoint &clientEndpoint);
    void updateLastResponse(udp::endpoint &clientEndpoint);

    std::string getClientUniqueString(udp::endpoint &clientEndpoint);

    void updateConsoleTitle();
};