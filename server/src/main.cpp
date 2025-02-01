#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/asio.hpp>

#include "MessageHandler.h"
#include "Data.h"

using boost::asio::ip::udp;

struct ClientInfo
{
    udp::endpoint endpoint;
    std::chrono::steady_clock::time_point last_seen;
};

std::unordered_map<std::string, ClientInfo> clients;
MessageHandler messageHandler;

std::string getClientUniqueString(udp::endpoint clientEndpoint)
{
    std::string clientPortIp = clientEndpoint.address().to_string() + ":";
    clientPortIp += std::to_string(clientEndpoint.port());
    return clientPortIp;
}

void updateConsoleTitle(){
    std::string title = "Players: " + std::to_string(clients.size());
    SetConsoleTitle(title.c_str());
}

void removeClient(udp::endpoint clientEndpoint)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);
    auto it = clients.find(clientPortIp);
    if (it != clients.end())
        clients.erase(it);

    updateConsoleTitle();
}

void addNewClient(udp::endpoint clientEndpoint)
{
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    auto [it, inserted] = clients.try_emplace(clientPortIp, ClientInfo{clientEndpoint});
    if (inserted)
        std::cout << "Added new Client: " << clientPortIp << "\n";

    updateConsoleTitle();
}

void handleBuffer(udp::socket *socket, udp::endpoint clientEndpoint, std::string buffer)
{
    addNewClient(clientEndpoint);

    Data data;
    data.deserialize(buffer);
    std::cout << "ID: " << data.id << "\n";
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    Data package102;
    package102.id = 101;
    package102.names.push_back(clientPortIp);
    // coords
    package102.names.push_back(data.names.at(0));
    package102.names.push_back(data.names.at(1));
    package102.names.push_back(data.names.at(2));
    // rotation
    package102.names.push_back(data.names.at(3));
    package102.names.push_back(data.names.at(4));
    package102.names.push_back(data.names.at(5));
    // isPlayerRunning
    package102.names.push_back(data.names.at(6));

    std::string serializedPacket = package102.serialize();

    if (data.id == 101)
    {
        for (const auto &[key, clientInfo] : clients)
        {
            if (key == clientPortIp)
            {
                continue;
            }

            std::cout << "\t" << key << " | " << clientPortIp << "\n";

            socket->send_to(boost::asio::buffer(serializedPacket), clientInfo.endpoint);
            std::cout << "\t" << serializedPacket << "\n";
            // std::cout << "Key: " << key << ", Client ID: " << clientInfo.id << "\n";
        }
    }
}

int main()
{
    try
    {
        boost::asio::io_context io_context;

        // Server-Socket on Port 12345
        udp::socket socket(io_context, udp::endpoint(udp::v4(), 12345));
        std::cout << "UDP-Server started on Port 12345..." << std::endl;

        // Datenpuffer und Endpoint für asynchronen Empfang
        auto buffer = std::make_shared<std::array<char, 1024>>();
        auto sender_endpoint = std::make_shared<udp::endpoint>();

        // Empfangshandler
        std::function<void(const boost::system::error_code &, std::size_t)> receive_handler;
        receive_handler = [&](const boost::system::error_code &error, std::size_t bytes_received)
        {
            
            if (!error)
            {
                std::cout << "Received something: " << bytes_received << " bytes\n";

                // Daten an handleBuffer übergeben
                boost::asio::post(io_context, [sender_endpoint, buffer, bytes_received, &socket]()
                                  {
                    std::string receivedPackage = std::string(buffer->data(), bytes_received);
                    handleBuffer(&socket, *sender_endpoint, receivedPackage); });

                // Weiter auf Nachrichten warten
                socket.async_receive_from(boost::asio::buffer(*buffer), *sender_endpoint, receive_handler);
            }
            else
            {
                //std::string clientId = getClientUniqueString(*sender_endpoint);
                std::cerr << "\nError receiving: " << error.message() << "\n";
                removeClient(*sender_endpoint);
                socket.async_receive_from(boost::asio::buffer(*buffer), *sender_endpoint, receive_handler);
            }
        };

        // Erste Empfangsanfrage starten
        socket.async_receive_from(boost::asio::buffer(*buffer), *sender_endpoint, receive_handler);

        // Threads für den io_context-Thread-Pool erstellen
        const size_t thread_count = std::thread::hardware_concurrency();
        std::cout << "Using " << thread_count << " threads.\n";

        std::vector<std::thread> threads;
        for (size_t i = 0; i < thread_count; ++i)
        {
            threads.emplace_back([&io_context]()
                                 { io_context.run(); });
        }

        // Warten, bis alle Threads beendet sind
        for (auto &thread : threads)
        {
            thread.join();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Fehler: " << e.what() << std::endl;
    }
    return 0;
}