#include "ServerManager.h"

ServerManager::ServerManager(boost::asio::io_context &io_context, boost::asio::io_context &processing_context) : socket(io_context, udp::endpoint(udp::v4(), 12345)){

    this->processing_context = &processing_context;
    std::cout << "UDP-Server started on Port 12345..." << std::endl;

    messageHandler = new MessageHandler(clients);

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

                    messageHandler->handleBuffer(&socket, *sender_endpoint, receivedPackage);
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