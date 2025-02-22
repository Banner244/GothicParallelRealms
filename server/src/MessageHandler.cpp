#include "MessageHandler.h"

MessageHandler::MessageHandler(std::unordered_map<std::string, CommonStructures::ClientInfo> &clients, udp::socket &socket)
{   
    this->clients = &clients;
    this->pSocket = &socket;
}

void MessageHandler::handleBuffer(udp::endpoint &clientEndpoint, std::string buffer)
{
    addNewClient(clientEndpoint);
    updateLastResponse(clientEndpoint);
    /*Data data;
    data.deserialize(buffer);*/
    //PackagingSystem::ReadPacketId
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
    std::string clientPortIp = getClientUniqueString(clientEndpoint);
    std::cout << clientPortIp << " responded to Heartbeat Request\n";
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

    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        for (auto it = clients->begin(); it != clients->end(); ++it)
        {
            sendMessage(it->second.endpoint, serializedPacket);
        }
    }
}
void MessageHandler::clientSharesAnimations(udp::endpoint &clientEndpoint, std::string &buffer)
{
    auto safeBuffer = std::make_shared<std::string>(buffer);
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    PackagingSystem animationPacket(Packets::ServerPacket::serverDistributeAnimations);

    animationPacket.addString(clientPortIp);
    animationPacket.addInt(PackagingSystem::ReadItem<int>(*safeBuffer));

    std::string serializedPacket = animationPacket.serializePacket();
    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        for (auto it = clients->begin(); it != clients->end(); ++it)
        {
            sendMessage(it->second.endpoint, serializedPacket);
        }
    }
}

void MessageHandler::sendMessage(udp::endpoint &clientEndpoint, std::string buffer)
{
    auto packetPtr = std::make_shared<std::string>(buffer);
    pSocket->async_send_to(
        boost::asio::buffer(*packetPtr),
        clientEndpoint,
        [packetPtr, clientEndpoint](boost::system::error_code ec, std::size_t bytes_sent)
        {
            if (ec)
            {
                std::cerr << "Async send error to " << clientEndpoint << ": " << ec.message() << std::endl;
            }
            else
            {
                std::cout << "Gesendet (" << bytes_sent << " Bytes) an " << clientEndpoint << std::endl;
                std::cout << *packetPtr << std::endl;
            }
        });
}

void MessageHandler::removeClient(udp::endpoint &clientEndpoint)
{
    std::lock_guard<std::mutex> lock(clients_mutex);
    std::string clientPortIp = getClientUniqueString(clientEndpoint);
    auto it = clients->find(clientPortIp);
    if (it != clients->end())
        clients->erase(it);

    updateConsoleTitle();
}

void MessageHandler::addNewClient(udp::endpoint &clientEndpoint)
{
    std::lock_guard<std::mutex> lock(clients_mutex);
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    CommonStructures::ClientInfo clientInfo;
    clientInfo.endpoint = clientEndpoint;
    clientInfo.lastResponse = std::chrono::high_resolution_clock::now();

    auto [it, inserted] = clients->try_emplace(clientPortIp, clientInfo);
    if (inserted)
        std::cout << "Added new Client: " << clientPortIp << "\n";

    updateConsoleTitle();
}

void MessageHandler::updateLastResponse(udp::endpoint &clientEndpoint) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    std::string clientPortIp = getClientUniqueString(clientEndpoint);
    
    auto it = clients->find(clientPortIp);
    if (it != clients->end())
        it->second.lastResponse = std::chrono::high_resolution_clock::now();
}

std::string MessageHandler::getClientUniqueString(udp::endpoint &clientEndpoint)
{
    std::string clientPortIp = clientEndpoint.address().to_string() + ":";
    clientPortIp += std::to_string(clientEndpoint.port());
    return clientPortIp;
}

void MessageHandler::updateConsoleTitle()
{
    std::string title = "Players: " + std::to_string(clients->size());
    SetConsoleTitle(title.c_str());
}