#include "ServerManager.h"

ServerManager::ServerManager(boost::asio::io_context &io_context, boost::asio::io_context &processing_context) : socket(io_context, udp::endpoint(udp::v4(), 12345))
{

    this->processing_context = &processing_context;
    std::cout << "UDP-Server started on Port 12345..." << std::endl;
    serverRunning = true;
    messageHandler = new MessageHandler(*this, clients, socket);

    start_receive();
}

void ServerManager::start_receive()
{
    auto buffer = std::make_shared<std::array<char, 1024>>();
    auto sender_endpoint = std::make_shared<udp::endpoint>();

    socket.async_receive_from(
        boost::asio::buffer(*buffer), *sender_endpoint,
        [this, buffer, sender_endpoint](const boost::system::error_code &error, std::size_t bytes_received)
        {
            if (!error)
            {
                std::cout << "Received something: " << bytes_received << " bytes\n";

                boost::asio::post(*processing_context, [this, buffer, sender_endpoint, bytes_received]()
                                  {
                    std::string receivedPackage(buffer->data(), bytes_received);

                    messageHandler->handleBuffer(*sender_endpoint, receivedPackage); });

                start_receive();
            }
            else
            {
                std::cerr << "\nError receiving: " << error.message() << "\n";
                removeClient(*sender_endpoint);

                // Starte erneut den Empfang
                start_receive();
            }
        });
}

void ServerManager::watchingHeartbeat()
{

    while (serverRunning)
    {
        for (auto it = clients.begin(); it != clients.end(); ++it)
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = currentTime - it->second.lastResponse;
            int durrationInSec = static_cast<int>(elapsed.count() / 1000);

            if (durrationInSec >= 25)
            {
                //PackagingSystem heartbeatRequest(Packets::ServerPacket::serverRemoveDisconnectedClient);
                // Create a Class for basic client management and sending messages and for passing it on
                removeClient(it->second.endpoint);

            }

            if (durrationInSec >= 5)
            {
                std::cout << "Elapsed Time: " << durrationInSec << " seconds" << std::endl;

                // Sending every 5 Seconds a Heartbeat request
                if (durrationInSec % 5 == 0)
                {
                    PackagingSystem heartbeatRequest(Packets::ServerPacket::serverRequestHeartbeat);
                    sendMessage(it->second.endpoint, heartbeatRequest.serializePacket());
                }
            }
        }

        Sleep(1000);
    }
}


void ServerManager::sendMessage(udp::endpoint &clientEndpoint, std::string buffer)
{
    auto packetPtr = std::make_shared<std::string>(buffer);
    socket.async_send_to(
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

void ServerManager::removeClient(udp::endpoint &clientEndpoint)
{
    std::lock_guard<std::mutex> lock(clients_mutex);
    std::string clientPortIp = getClientUniqueString(clientEndpoint);
    auto it = clients.find(clientPortIp);
    if (it != clients.end())
        clients.erase(it);

    updateConsoleTitle();
}

void ServerManager::addNewClient(udp::endpoint &clientEndpoint)
{
    std::lock_guard<std::mutex> lock(clients_mutex);
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    CommonStructures::ClientInfo clientInfo;
    clientInfo.endpoint = clientEndpoint;
    clientInfo.lastResponse = std::chrono::high_resolution_clock::now();

    auto [it, inserted] = clients.try_emplace(clientPortIp, clientInfo);
    if (inserted)
        std::cout << "Added new Client: " << clientPortIp << "\n";

    updateConsoleTitle();
}

void ServerManager::updateLastResponse(udp::endpoint &clientEndpoint) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    std::string clientPortIp = getClientUniqueString(clientEndpoint);
    
    auto it = clients.find(clientPortIp);
    if (it != clients.end())
        it->second.lastResponse = std::chrono::high_resolution_clock::now();
}

std::string ServerManager::getClientUniqueString(udp::endpoint &clientEndpoint)
{
    std::string clientPortIp = clientEndpoint.address().to_string() + ":";
    clientPortIp += std::to_string(clientEndpoint.port());
    return clientPortIp;
}

void ServerManager::updateConsoleTitle()
{
    std::string title = "Players: " + std::to_string(clients.size());
    SetConsoleTitle(title.c_str());
}