#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/asio.hpp>

#include "Data.h"

using boost::asio::ip::udp;


struct ClientInfo {
    udp::endpoint endpoint;
    std::chrono::steady_clock::time_point last_seen;
};

std::unordered_map<std::string, ClientInfo> clients;

void addNewClient(udp::endpoint clientEndpoint){
    ClientInfo newClient;
    newClient.endpoint = clientEndpoint;

    std::string clientPortIp = clientEndpoint.address().to_string();
    clients[clientPortIp] = newClient;

        //std::this_thread::sleep_for(std::chrono::milliseconds(100));

}

void handleBuffer(udp::socket *socket, udp::endpoint clientEndpoint, std::string buffer) {
    addNewClient(clientEndpoint);
    std::cout << "\tBUfferHandler " << "\n";
    //const std::string msgBuffer;
    
    Data data;
    data.deserialize(buffer);
    std::cout << "ID: "<< data.id << "\n";

    for (const auto& [key, clientInfo] : clients) {
        std::cout << "\t Going through loop " << "\n";
        if(key == clientEndpoint.address().to_string())
            continue;
        
        std::string msg = "Does it work?";
        socket->send_to(boost::asio::buffer(msg), clientInfo.endpoint);
        //std::cout << "Key: " << key << ", Client ID: " << clientInfo.id << "\n";
    }

    /*for(int i =0; i< data.names.size(); i++){
        std::cout << data.id << data.names.at(i) << "\n";
    }*/

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

/*int main() {
    try {
        boost::asio::io_context io_context;

            const size_t thread_count = std::thread::hardware_concurrency();
            std::cout << "Using " << thread_count << " threads.\n";

            // Threads erstellen
            std::vector<std::thread> threads;
            for (size_t i = 0; i < thread_count; ++i) {
                threads.emplace_back([&io_context]() {
                    io_context.run();
                });
            }
            

        // Server-Socket on Port 12345
        udp::socket socket(io_context, udp::endpoint(udp::v4(), 12345));

        std::cout << "UDP-Server started on Port 12345..." << std::endl;

        while (true) {
            char buffer[1024];
            udp::endpoint sender_endpoint;

            // Receive Data 
            std::size_t bytes_received = socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);
            std::cout << "Received something: " << bytes_received << " bytes" << "\n";

            boost::asio::post(io_context, [sender_endpoint, buffer, bytes_received]() { 
                handleBuffer(sender_endpoint, std::string(buffer, bytes_received));
            });

        
        }


        // Warten, bis alle Threads fertig sind
        for (auto& thread : threads) {
            thread.join();
        }
    } catch (std::exception& e) {
        std::cerr << "Fehler: " << e.what() << std::endl;
    }
    return 0;
}*/





            /*std::cout << "Received: " << std::string(buffer, bytes_received)
                      << " from " << sender_endpoint.address().to_string() << ":"
                      << sender_endpoint.port() << std::endl;

            // send Answer
            std::string reply = "Got the Message!!";
            socket.send_to(boost::asio::buffer(reply), sender_endpoint);*/