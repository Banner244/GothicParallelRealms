#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/asio.hpp>

#include "MessageHandler.h"
#include "Data.h"

using boost::asio::ip::udp;

struct ClientInfo {
    udp::endpoint endpoint;
    std::chrono::steady_clock::time_point last_seen;
};

std::unordered_map<std::string, ClientInfo> clients;
MessageHandler messageHandler;


std::string getClientUniqueString(udp::endpoint clientEndpoint) {
    std::string clientPortIp =clientEndpoint.address().to_string()+ ":";
    clientPortIp += std::to_string(clientEndpoint.port());
    return clientPortIp;
}

void addNewClient(udp::endpoint clientEndpoint) {
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    auto [it, inserted] = clients.try_emplace(clientPortIp, ClientInfo{clientEndpoint});
    if (inserted) 
        std::cout << "Added new Client: " << clientPortIp << "\n";
}

void handleBuffer(udp::socket *socket, udp::endpoint clientEndpoint, std::string buffer) {
    addNewClient(clientEndpoint);

    Data data;
    data.deserialize(buffer);
    std::cout << "ID: "<< data.id << "\n";
    std::string clientPortIp = getClientUniqueString(clientEndpoint);

    if(data.id == 101) {
        for (auto it = clients.begin(); it != clients.end(); ) {
            const auto& [key, clientInfo] = *it;

            if (key == clientPortIp) {
                ++it; // Weiter zum nächsten Element
                continue;
            }

            std::cout << "\t" << key << " | " << clientPortIp << "\n";

            Data package102;
            package102.id = 101;
            package102.names.push_back(clientPortIp);
            package102.names.push_back(data.names.at(0));
            package102.names.push_back(data.names.at(1));
            package102.names.push_back(data.names.at(2));

            socket->send_to(boost::asio::buffer(package102.serialize()), clientInfo.endpoint);
            std::cout << package102.serialize() << "\n";
        }
    }
}

int main() {
    try {
        boost::asio::io_context io_context;

        // Server-Socket on Port 12345
        udp::socket socket(io_context, udp::endpoint(udp::v4(), 12345));
        std::cout << "UDP-Server started on Port 12345..." << std::endl;

        // Datenpuffer und Endpoint für asynchronen Empfang
        auto buffer = std::make_shared<std::array<char, 1024>>();
        auto sender_endpoint = std::make_shared<udp::endpoint>();

        // Empfangshandler
        std::function<void(const boost::system::error_code&, std::size_t)> receive_handler;
        receive_handler = [&](const boost::system::error_code& error, std::size_t bytes_received) {
            if (!error) {
                std::cout << "Received something: " << bytes_received << " bytes\n";

                // Daten an handleBuffer übergeben
                boost::asio::post(io_context, [sender_endpoint, buffer, bytes_received, &socket]() {
                    std::string receivedPackage = std::string(buffer->data(), bytes_received);
                    handleBuffer(&socket, *sender_endpoint, receivedPackage);
                });

                // Weiter auf Nachrichten warten
                socket.async_receive_from(
                    boost::asio::buffer(*buffer), *sender_endpoint, receive_handler);
            } else {
                std::cerr << "Error receiving: " << error.message() << "\n";
            }
        };

        // Erste Empfangsanfrage starten
        socket.async_receive_from(boost::asio::buffer(*buffer), *sender_endpoint, receive_handler);

        // Threads für den io_context-Thread-Pool erstellen
        const size_t thread_count = std::thread::hardware_concurrency();
        std::cout << "Using " << thread_count << " threads.\n";

        std::vector<std::thread> threads;
        for (size_t i = 0; i < thread_count; ++i) {
            threads.emplace_back([&io_context]() {
                io_context.run();
            });
        }

        // Warten, bis alle Threads beendet sind
        for (auto& thread : threads) {
            thread.join();
        }
    } catch (std::exception& e) {
        std::cerr << "Fehler: " << e.what() << std::endl;
    }
    return 0;
}