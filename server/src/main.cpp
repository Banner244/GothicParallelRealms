#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/asio.hpp>

#include "ServerManager.h"

#include "MessageHandler.h"
#include "Data.h"

using boost::asio::ip::udp;

struct ClientInfo
{
    udp::endpoint endpoint;
    std::chrono::steady_clock::time_point last_seen;
};

std::unordered_map<std::string, ClientInfo> clients;
std::mutex clients_mutex;
//MessageHandler messageHandler;

std::string getClientUniqueString(udp::endpoint &clientEndpoint)
{
    std::string clientPortIp = clientEndpoint.address().to_string() + ":";
    clientPortIp += std::to_string(clientEndpoint.port());
    return clientPortIp;
}

void updateConsoleTitle(){
    std::string title = "Players: " + std::to_string(clients.size());
    SetConsoleTitle(title.c_str());
}

void removeClient(udp::endpoint &clientEndpoint)
{
    std::lock_guard<std::mutex> lock(clients_mutex); 
    std::string clientPortIp = getClientUniqueString(clientEndpoint);
    auto it = clients.find(clientPortIp);
    if (it != clients.end())
        clients.erase(it);

    updateConsoleTitle();
}

void addNewClient(udp::endpoint &clientEndpoint)
{
    std::lock_guard<std::mutex> lock(clients_mutex); 
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    auto [it, inserted] = clients.try_emplace(clientPortIp, ClientInfo{clientEndpoint});
    if (inserted)
        std::cout << "Added new Client: " << clientPortIp << "\n";

    updateConsoleTitle();
}

void handleBuffer(udp::socket *socket, udp::endpoint &clientEndpoint, std::string buffer)
{
    addNewClient(clientEndpoint);

    Data data;
    data.deserialize(buffer);
    std::cout << "ID: " << data.id << std::endl;
    std::cout << "Message: " << buffer << std::endl;
    std::string clientPortIp = getClientUniqueString(clientEndpoint);



    if (data.id == 101)
    {
    // Erstelle das zu sendende Paket
    Data package102;
    package102.id = 101;
    package102.names.push_back(clientPortIp);
    package102.names.insert(package102.names.end(), data.names.begin(), data.names.end());

    std::string serializedPacket = package102.serialize();


        // copy to keep clients safe
        std::vector<udp::endpoint> clientEndpoints;
        {
            std::lock_guard<std::mutex> lock(clients_mutex); 
            for (const auto &[key, clientInfo] : clients)
            {
                /*if (key != clientPortIp)
                {
                    clientEndpoints.push_back(clientInfo.endpoint);
                }*/
               clientEndpoints.push_back(clientInfo.endpoint);
            }
        }

        // sending players information
        for (const auto &endpoint : clientEndpoints)
        {
            std::lock_guard<std::mutex> lock(clients_mutex); 
            // to keep the string safe
            auto packetPtr = std::make_shared<std::string>(serializedPacket);

            socket->async_send_to(
                boost::asio::buffer(*packetPtr),
                endpoint,
                [packetPtr, endpoint](boost::system::error_code ec, std::size_t bytes_sent)
                {
                    if (ec)
                    {
                        std::cerr << "Async send error to " << endpoint << ": " << ec.message() << std::endl;
                    }
                    else
                    {
                        std::cout << "Gesendet (" << bytes_sent << " Bytes) an " << endpoint << std::endl;
                        std::cout << *packetPtr << std::endl;
                    }
                });
        }
    }
    else if (data.id == 102)
    {
            // Erstelle das zu sendende Paket
    Data package102;
    package102.id = 102;
    package102.names.push_back(clientPortIp);
    package102.names.insert(package102.names.end(), data.names.begin(), data.names.end());

    std::string serializedPacket = package102.serialize();
        // copy to keep clients safe
        std::vector<udp::endpoint> clientEndpoints;
        {
            std::lock_guard<std::mutex> lock(clients_mutex); 
            for (const auto &[key, clientInfo] : clients)
            {
                /*if (key != clientPortIp)
                {
                    clientEndpoints.push_back(clientInfo.endpoint);
                }*/
               clientEndpoints.push_back(clientInfo.endpoint);
            }
        }

        // sending players information
        for (const auto &endpoint : clientEndpoints)
        {
            std::lock_guard<std::mutex> lock(clients_mutex); 
            // to keep the string safe
            auto packetPtr = std::make_shared<std::string>(serializedPacket);

            socket->async_send_to(
                boost::asio::buffer(*packetPtr),
                endpoint,
                [packetPtr, endpoint](boost::system::error_code ec, std::size_t bytes_sent)
                {
                    if (ec)
                    {
                        std::cerr << "Async send error to " << endpoint << ": " << ec.message() << std::endl;
                    }
                    else
                    {
                        std::cout << "Gesendet (" << bytes_sent << " Bytes) an " << endpoint << std::endl;
                        std::cout << *packetPtr << std::endl;
                    }
                });
        }
    }
}

int main()
{
    try
    {
        boost::asio::io_context io_context;
        boost::asio::io_context processing_context;
        boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard(processing_context.get_executor());

        ServerManager ServerManager(io_context, processing_context);
        // Server-Socket on Port 12345
        /*udp::socket socket(io_context, udp::endpoint(udp::v4(), 12345));
        std::cout << "UDP-Server started on Port 12345..." << std::endl;

        auto buffer = std::make_shared<std::array<char, 1024>>();
        auto sender_endpoint = std::make_shared<udp::endpoint>();

        std::function<void(const boost::system::error_code &, std::size_t)> receive_handler;
        receive_handler = [&](const boost::system::error_code &error, std::size_t bytes_received)
        {
            
            if (!error)
            {
                std::cout << "Received something: " << bytes_received << " bytes\n";

                boost::asio::post(processing_context, [sender_endpoint, buffer, bytes_received, &socket]() {
                    std::string receivedPackage = std::string(buffer->data(), bytes_received);
                    
                    handleBuffer(&socket, *sender_endpoint, receivedPackage);
                });

                socket.async_receive_from(boost::asio::buffer(*buffer), *sender_endpoint, receive_handler);
            }
            else
            {
                std::cerr << "\nError receiving: " << error.message() << "\n";
                removeClient(*sender_endpoint);
                socket.async_receive_from(boost::asio::buffer(*buffer), *sender_endpoint, receive_handler);
            }
        };


        // starting receiving
        socket.async_receive_from(boost::asio::buffer(*buffer), *sender_endpoint, receive_handler);*/

        const size_t thread_count = std::max(1u, std::thread::hardware_concurrency() / 2);
        std::cout << "Using " << thread_count << " network threads.\n";

        std::vector<std::thread> threads;
        for (size_t i = 0; i < thread_count; ++i)
        {
            threads.emplace_back([&io_context]()
                                 { io_context.run(); });
        }

        const size_t processing_threads = std::max(1u, std::thread::hardware_concurrency() / 2);
        std::cout << "Using " << processing_threads << " processing threads.\n";
        for (size_t i = 0; i < processing_threads; ++i)
        {
            threads.emplace_back([&processing_context]() { processing_context.run(); });
        }

        // waiting for the end of all threads
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