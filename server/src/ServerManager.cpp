#include "ServerManager.h"

ServerManager::ServerManager(boost::asio::io_context &io_context, boost::asio::io_context &processing_context) : socket(io_context, udp::endpoint(udp::v4(), 12345)){

    this->processing_context = &processing_context;
    std::cout << "UDP-Server started on Port 12345..." << std::endl;
    serverRunning = true;
    messageHandler = new MessageHandler(clients, socket);

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

                boost::asio::post(*processing_context, [this, buffer, sender_endpoint, bytes_received]() {
                    std::string receivedPackage(buffer->data(), bytes_received);

                    messageHandler->handleBuffer(*sender_endpoint, receivedPackage);
                });

                // Starte den nächsten Empfang mit einem neuen Buffer!
                start_receive();
            }
            else
            {
                std::cerr << "\nError receiving: " << error.message() << "\n";
                messageHandler->removeClient(*sender_endpoint);

                // Starte erneut den Empfang
                start_receive();
            }
        });
}

void ServerManager::watchingHeartbeat() {
    while(serverRunning) {
        {
            for (auto it = clients.begin(); it != clients.end(); ++it)
            {
                auto currentTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed = currentTime - it->second.lastResponse;
                int durrationInSec = static_cast<int>(elapsed.count()/1000);

                if(durrationInSec >= 25) {
                    messageHandler->removeClient(it->second.endpoint);
                }

                if( durrationInSec >= 5) {
                    std::cout << "Elapsed Time: " << durrationInSec << " seconds" << std::endl;

                    // Sending every 5 Seconds a Heartbeat request
                    if(durrationInSec % 5 == 0){
                        PackagingSystem heartbeatRequest(Packets::ServerPacket::serverRequestHeartbeat);
                        messageHandler->sendMessage(it->second.endpoint, heartbeatRequest.serializePacket());
                    }   
                }


            }
        }

        Sleep(1000);
    }

}