#pragma once

#include <iostream>

#include <boost/asio.hpp>

#include "Data.h"

#include "PacketIDs.h"


using boost::asio::ip::udp;

class MessageHandler
{

public:
    MessageHandler(std::unordered_map<std::string, udp::endpoint> &clients);
    void handleBuffer(udp::socket *socket, udp::endpoint &clientEndpoint, std::string buffer);

    void MessageHandler::removeClient(udp::endpoint &clientEndpoint);

private:
    std::unordered_map<std::string, udp::endpoint> *clients;
    std::mutex clients_mutex;

    void clientSharesPosition(udp::socket *socket, udp::endpoint &clientEndpoint, Data data);
    void clientSharesAnimations(udp::socket *socket, udp::endpoint &clientEndpoint, Data data);

    void sendMessage(udp::socket *socket, udp::endpoint &clientEndpoint, std::string buffer);


    

    void MessageHandler::addNewClient(udp::endpoint &clientEndpoint);

    std::string MessageHandler::getClientUniqueString(udp::endpoint &clientEndpoint);

    void MessageHandler::updateConsoleTitle();
};