#include "MessageHandler.h"

MessageHandler::MessageHandler(ServerManager &serverManager, std::unordered_map<std::string, CommonStructures::ClientInfo> &clients, udp::socket &socket)
{   
    this->pServerManager = &serverManager;
    this->clients = &clients;
    this->pSocket = &socket;
}

void MessageHandler::handleBuffer(udp::endpoint &clientEndpoint, std::string buffer)
{
    pServerManager->addNewClient(clientEndpoint);
    pServerManager->updateLastResponse(clientEndpoint);

    int id = PackagingSystem::ReadPacketId(buffer);
    Packets::ClientPacket packetId = static_cast<Packets::ClientPacket>(id);

    //Packets:: packetId = data.id;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Message: " << buffer << std::endl;

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
        std::cout << "Unknown Paket...\n"
                  << std::endl;
        break;
    }
}

void MessageHandler::clientRepondsHeartbeat(udp::endpoint &clientEndpoint, std::string &buffer) {
    std::string clientPortIp = pServerManager->getClientUniqueString(clientEndpoint);
    std::cout << clientPortIp << " responded to Heartbeat Request\n";
}

void MessageHandler::clientSharesPosition(udp::endpoint &clientEndpoint, std::string &buffer)
{
    std::string clientPortIp = pServerManager->getClientUniqueString(clientEndpoint);

    PackagingSystem positionPacket(Packets::ServerPacket::serverDistributePosition);
    positionPacket.addString(clientPortIp);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(buffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(buffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(buffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(buffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(buffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(buffer), 2);

    std::string serializedPacket = positionPacket.serializePacket();

    {
        std::lock_guard<std::mutex> lock(pServerManager->clients_mutex);
        for (auto it = clients->begin(); it != clients->end(); ++it)
        {
            pServerManager->sendMessage(it->second.endpoint, serializedPacket);
        }
    }
}
void MessageHandler::clientSharesAnimations(udp::endpoint &clientEndpoint, std::string &buffer)
{
    auto safeBuffer = std::make_shared<std::string>(buffer);
    std::string clientPortIp = pServerManager->getClientUniqueString(clientEndpoint);

    PackagingSystem animationPacket(Packets::ServerPacket::serverDistributeAnimations);

    animationPacket.addString(clientPortIp);
    animationPacket.addInt(PackagingSystem::ReadItem<int>(*safeBuffer));

    std::string serializedPacket = animationPacket.serializePacket();
    {
        std::lock_guard<std::mutex> lock(pServerManager->clients_mutex);
        for (auto it = clients->begin(); it != clients->end(); ++it)
        {
            pServerManager->sendMessage(it->second.endpoint, serializedPacket);
        }
    }
}
