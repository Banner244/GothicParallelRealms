#include "MessageHandler.h"

MessageHandler::MessageHandler(AsyncUnorderedMap<std::string, CommonStructures::ClientInfo> &clients, udp::socket &socket)
{
    this->clients = &clients;
    this->pSocket = &socket;
}

void MessageHandler::handleBuffer(udp::endpoint &clientEndpoint, std::string buffer)
{
    addNewClient(clientEndpoint);
    updateLastResponse(clientEndpoint);

    int id = PackagingSystem::ReadPacketId(buffer);
    Packets::ClientPacket packetId = static_cast<Packets::ClientPacket>(id);

    Async::PrintLn( "ID: " + std::to_string(id) );
    Async::PrintLn( "Message: " + buffer );

    switch (packetId)
    {
    case Packets::ClientPacket::clientResponseHeartbeat:
        clientRepondsHeartbeat(clientEndpoint, buffer);
        break;
    case Packets::ClientPacket::clientSharePosition:
        clientSharesPosition(clientEndpoint, buffer);
        break;
    case Packets::ClientPacket::clientShareAnimations:
        clientSharesAnimations(clientEndpoint, buffer);
        break;
    default:
        Async::PrintLn("Unknown Paket...");
        break;
    }
}

void MessageHandler::clientRepondsHeartbeat(udp::endpoint &clientEndpoint, std::string &buffer)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);
    Async::PrintLn( clientPortIp + " responded to Heartbeat Request");
}

void MessageHandler::clientSharesPosition(udp::endpoint &clientEndpoint, std::string &buffer)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    PackagingSystem positionPacket(Packets::ServerPacket::serverDistributePosition);
    positionPacket.addString(clientPortIp);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(buffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(buffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(buffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(buffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(buffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(buffer), 2);

    std::string serializedPacket = positionPacket.serializePacket();

    sendToAllExceptSender(clientEndpoint, serializedPacket);
}
void MessageHandler::clientSharesAnimations(udp::endpoint &clientEndpoint, std::string &buffer)
{
    auto safeBuffer = std::make_shared<std::string>(buffer);
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    PackagingSystem animationPacket(Packets::ServerPacket::serverDistributeAnimations);

    animationPacket.addString(clientPortIp);
    int animationCount = PackagingSystem::ReadItem<int>(*safeBuffer);
    animationPacket.addInt(animationCount);

    for(int i = 0; i< animationCount; i++) {
        animationPacket.addInt(PackagingSystem::ReadItem<int>(*safeBuffer));
    }

    sendToAllExceptSender(clientEndpoint, animationPacket.serializePacket());
}

void MessageHandler::sendMessage(udp::endpoint &clientEndpoint, std::string buffer)
{
    auto packetPtr = std::make_shared<std::string>(buffer);
    pSocket->async_send_to(
        boost::asio::buffer(*packetPtr),
        clientEndpoint,
        [this, packetPtr, clientEndpoint](boost::system::error_code ec, std::size_t bytes_sent)
        {
            if (ec){
                //std::cerr << "Async send error to " << clientEndpoint << ": " << ec.message() << std::endl;
                Async::Cerr ("Async send error to " + endpointToString(clientEndpoint) + ": " + ec.message());
            } else {
                Async::PrintLn ("Gesendet (" + std::to_string(bytes_sent) + " Bytes) an " + endpointToString(clientEndpoint));
                Async::PrintLn(*packetPtr);
            }
        });
}
void MessageHandler::sendToAllExceptSender(udp::endpoint &senderEndpoint, std::string buffer)
{
    std::lock_guard<std::mutex> lock(clients->getMutex());
    for (auto it = clients->getUnorderedMap()->begin(); it != clients->getUnorderedMap()->end(); ++it)
    {
        //if (senderEndpoint != it->second.endpoint) // Uncomment for main branch
            sendMessage(it->second.endpoint, buffer);
    }
}

void MessageHandler::removeClient(udp::endpoint &clientEndpoint)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    if(clients->existsItem(clientPortIp))
        clients->remove(clientPortIp);

    std::lock_guard<std::mutex> lock(clients->getMutex());
    // Telling the Clients to remove unreachable client
    for (auto &pair : *clients->getUnorderedMap())
    {
        PackagingSystem clientToRemove(Packets::ServerPacket::serverRemoveClient);
        clientToRemove.addString(clientPortIp);
        sendMessage(pair.second.endpoint, clientToRemove.serializePacket());
    }

    updateConsoleTitle();
}

void MessageHandler::addNewClient(udp::endpoint &clientEndpoint)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    CommonStructures::ClientInfo clientInfo;
    clientInfo.endpoint = clientEndpoint;
    clientInfo.lastResponse = std::chrono::high_resolution_clock::now();

    /*auto [it, inserted] = clients->try_emplace(clientPortIp, clientInfo);
    if (inserted)
        Async::PrintLn( "Added new Client: " + clientPortIp );*/
    if(clients->existsItem(clientPortIp))
        return;

    clients->append(clientPortIp, clientInfo);
    Async::PrintLn( "Added new Client: " + clientPortIp );

    updateConsoleTitle();
}

void MessageHandler::updateLastResponse(udp::endpoint &clientEndpoint)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    auto it = clients->find(clientPortIp);
    if (it)
        it->get().lastResponse = std::chrono::high_resolution_clock::now();
}

std::string MessageHandler::getClientUniqueString(udp::endpoint &clientEndpoint)
{
    std::string clientPortIp = clientEndpoint.address().to_string() + ":";
    clientPortIp += std::to_string(clientEndpoint.port());
    return clientPortIp;
}

void MessageHandler::updateConsoleTitle()
{
    std::string title = "Players: " + std::to_string(clients->getUnorderedMap()->size());
    SetConsoleTitle(title.c_str());
}

std::string MessageHandler::endpointToString(const udp::endpoint &clientEndpoint){
    std::string endpointStr = clientEndpoint.address().to_string();
    endpointStr += ":" + std::to_string(clientEndpoint.port());
    return endpointStr;
}