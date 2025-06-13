#pragma once

#include <iostream>

#include <boost/asio.hpp>

//#include "Data.h"
#include "CommonStructures.h"


#include "../../common/src/Network/Packets.h"
#include "../../common/src/Network/PackagingSystem.h"
#include "../../common/src/Async/AsyncUnorderedMap.h"
#include "../../common/src/Async/Async.h"

using boost::asio::ip::udp;

class MessageHandler
{

public:
    MessageHandler(AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> &clients, udp::socket &socket);
    void handleBuffer(udp::endpoint &clientEndpoint, std::string buffer);

    void removeClient(udp::endpoint &clientEndpoint);

    void sendMessage(udp::endpoint &clientEndpoint, std::string buffer);
    void sendToAllExceptSender(udp::endpoint &senderEndpoint, std::string buffer);
private:
    AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> *clients;
    udp::socket * pSocket;

    void clientHandshakeRequest(udp::endpoint &clientEndpoint, std::string &buffer);
    void clientRepondsHeartbeat(udp::endpoint &clientEndpoint, std::string &buffer);
    void clientSharesPosition(udp::endpoint &clientEndpoint, std::string &buffer);
    void clientSharesAnimations(udp::endpoint &clientEndpoint, std::string &buffer);

    
    bool isClientRegistered(udp::endpoint &clientEndpoint);

    bool addNewClient(udp::endpoint &clientEndpoint, std::string &username);
    void updateLastResponse(udp::endpoint &clientEndpoint);

    std::string getClientUniqueString(udp::endpoint &clientEndpoint);

    void updateConsoleTitle();

    std::string endpointToString(const udp::endpoint &clientEndpoint);
};