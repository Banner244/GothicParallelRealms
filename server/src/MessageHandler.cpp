#include "MessageHandler.h"

MessageHandler::MessageHandler(std::unordered_map<std::string, udp::endpoint> &clients)
{
    this->clients = &clients;
}

void MessageHandler::handleBuffer(udp::socket *socket, udp::endpoint &clientEndpoint, std::string buffer)
{
    addNewClient(clientEndpoint);

    Data data;
    data.deserialize(buffer);

    int packetId = data.id;
    std::cout << "ID: " << packetId << std::endl;
    std::cout << "Message: " << buffer << std::endl;

    switch ((ClientPacket)packetId)
    {
    case ClientPacket::clientSharePosition:
        clientSharesPosition(socket, clientEndpoint, data);
        break;
    case ClientPacket::clientShareAnimations:
        clientSharesAnimations(socket, clientEndpoint, data);
        break;

    case ClientPacket::clientShareRotation:
        clientSharesRotation(socket, clientEndpoint, data);
        break;
    default:
        std::cout << "Unknown Paket...\n"
                  << std::endl;
        break;
    }
}

void MessageHandler::clientSharesPosition(udp::socket *socket, udp::endpoint &clientEndpoint, Data data)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    Data newData;
    newData.id = ServerPacket::serverDistributePosition;
    newData.names.push_back(clientPortIp);
    newData.names.insert(newData.names.end(), data.names.begin(), data.names.end());

    std::string serializedPacket = newData.serialize();

    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        for (auto it = clients->begin(); it != clients->end(); ++it)
        {
            sendMessage(socket, it->second, serializedPacket);
        }
    }
}

void MessageHandler::clientSharesAnimations(udp::socket *socket, udp::endpoint &clientEndpoint, Data data)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    Data newData;
    newData.id = ServerPacket::serverDistributeAnimations;
    newData.names.push_back(clientPortIp);
    newData.names.insert(newData.names.end(), data.names.begin(), data.names.end());

    std::string serializedPacket = newData.serialize();

    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        for (auto it = clients->begin(); it != clients->end(); ++it)
        {
            sendMessage(socket, it->second, serializedPacket);
        }
    }
}

void MessageHandler::clientSharesRotation(udp::socket *socket, udp::endpoint &clientEndpoint, Data data)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    Data newData;
    newData.id = ServerPacket::serverDistributeRotation;
    newData.names.push_back(clientPortIp);
    newData.names.insert(newData.names.end(), data.names.begin(), data.names.end());

    std::string serializedPacket = newData.serialize();
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