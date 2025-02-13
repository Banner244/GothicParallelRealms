#include "MessageHandler.h"

MessageHandler::MessageHandler(std::unordered_map<std::string, udp::endpoint> &clients)
{
    this->clients = &clients;
}

void MessageHandler::handleBuffer(udp::socket *socket, udp::endpoint &clientEndpoint, std::string buffer)
{
    addNewClient(clientEndpoint);

    /*Data data;
    data.deserialize(buffer);*/
    //PackagingSystem::ReadPacketId
    int id = PackagingSystem::ReadPacketId(buffer);
    Packets::ClientPacket packetId = (Packets::ClientPacket)id;

    //Packets:: packetId = data.id;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Message: " << buffer << std::endl;

    switch (packetId)
    {
    case Packets::ClientPacket::clientSharePosition:
        clientSharesPosition(socket, clientEndpoint, buffer);
        break;
    /*case Packets::ClientPacket::clientShareAnimations:
        clientSharesAnimations(socket, clientEndpoint, buffer);
        break;*/
    default:
        std::cout << "Unknown Paket...\n"
                  << std::endl;
        break;
    }
}

void MessageHandler::clientSharesPosition(udp::socket *socket, udp::endpoint &clientEndpoint, std::string &buffer)
{
    auto safeBuffer = std::make_shared<std::string>(buffer);
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    /*Data package102;
    package102.id = 101;
    package102.names.push_back(clientPortIp);
    package102.names.insert(package102.names.end(), data.names.begin(), data.names.end());
    std::string serializedPacket = package102.serialize();*/
    PackagingSystem positionPacket(Packets::ServerPacket::serverDistributePosition);
    positionPacket.addString(clientPortIp);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(*safeBuffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(*safeBuffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(*safeBuffer), 2);
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(*safeBuffer));
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(*safeBuffer));
    positionPacket.addFloatPointNumber(PackagingSystem::ReadItem<double>(*safeBuffer));

    std::string serializedPacket = positionPacket.serializePacket();

    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        for (auto it = clients->begin(); it != clients->end(); ++it)
        {
            sendMessage(socket, it->second, serializedPacket);
        }
    }
}
void MessageHandler::clientSharesAnimations(udp::socket *socket, udp::endpoint &clientEndpoint, std::string &buffer)
{
    auto safeBuffer = std::make_shared<std::string>(buffer);
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    /*Data package102;
    package102.id = 102;
    package102.names.push_back(clientPortIp);
    package102.names.insert(package102.names.end(), data.names.begin(), data.names.end());
    std::string serializedPacket = package102.serialize();*/

    PackagingSystem animationPacket(Packets::ServerPacket::serverDistributePosition);

    animationPacket.addString(clientPortIp);
    animationPacket.addFloatPointNumber(PackagingSystem::ReadItem<int>(*safeBuffer));

    std::string serializedPacket = animationPacket.serializePacket();
    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        for (auto it = clients->begin(); it != clients->end(); ++it)
        {
            sendMessage(socket, it->second, serializedPacket);
        }
    }
}

void MessageHandler::sendMessage(udp::socket *socket, udp::endpoint &clientEndpoint, std::string buffer)
{
    auto packetPtr = std::make_shared<std::string>(buffer);
    socket->async_send_to(
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

    auto [it, inserted] = clients->try_emplace(clientPortIp, clientEndpoint);
    if (inserted)
        std::cout << "Added new Client: " << clientPortIp << "\n";

    updateConsoleTitle();
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