#include "ServerManager.h"
#include <queue>

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
                Async::PrintLn( "Received something: " + std::to_string(bytes_received) + " bytes");

                boost::asio::post(*processing_context, [this, buffer, sender_endpoint, bytes_received]() {
                    std::string receivedPackage(buffer->data(), bytes_received);

                    messageHandler->handleBuffer(*sender_endpoint, receivedPackage);
                });

                // repeat receiving
                start_receive();
            }
            else
            {
                Async::PrintLn( "\nError receiving: " + error.message());
                //std::cerr << "\nError receiving: " << error.message() << "\n";
                messageHandler->removeClient(*sender_endpoint);

                // repeat receiving
                start_receive();
            }
        });
}

void ServerManager::watchingHeartbeat() {
    while(serverRunning) {
        std::queue<udp::endpoint> endpointsToRemove;
        {
            std::lock_guard<std::mutex> lock(clients.getMutex());
            for (auto it = clients.getUnorderedMap()->begin(); it != clients.getUnorderedMap()->end(); ++it)
            {
                auto currentTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed = currentTime - it->second.lastResponse;
                int durrationInSec = static_cast<int>(elapsed.count()/1000);

                if(durrationInSec >= 10/*25*/) {
                    endpointsToRemove.push(it->second.endpoint);
                    //messageHandler->removeClient(it->second.endpoint);
                } else if( durrationInSec >= 5) {
                    //std::cout << "Elapsed Time: " << durrationInSec << " seconds" << std::endl;
                    Async::PrintLn( "Elapsed Time: " + std::to_string(durrationInSec) + " seconds");
                    // Sending every 5 Seconds a Heartbeat request
                    if(durrationInSec % 5 == 0){
                        PackagingSystem heartbeatRequest(Packets::ServerPacket::serverRequestHeartbeat);
                        messageHandler->sendMessage(it->second.endpoint, heartbeatRequest.serializePacket());
                    }   
                }
            }
        }

        while (!endpointsToRemove.empty()) {
            udp::endpoint endpoint = endpointsToRemove.front(); 
            endpointsToRemove.pop(); 
            messageHandler->removeClient(endpoint); 
        }
        Sleep(1000);
    }

}