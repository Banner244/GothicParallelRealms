#include "Client.h"

Client::Client(boost::asio::io_context &io_context, const std::string &host, const std::string &port, std::unordered_map<std::string, Npc*> *clients)
    : socket_(io_context), resolver_(io_context), server_endpoint_(*resolver_.resolve(udp::v4(), host, port).begin())
{
    this->clients = clients;
    messageHandler = new MessageHandler(clients);

    socket_.open(udp::v4());
    start_receive();
}

void Client::send_message(const std::string &message)
{
    socket_.async_send_to(
        boost::asio::buffer(message),
        server_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_sent)
        {
            if (ec)
                std::cerr << "Error sending: " << ec.message() << std::endl;
            else
                std::cout << "Sent " << bytes_sent << " bytes." << std::endl;
        });
}

void Client::start_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_),
        sender_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_received)
        {
            if (!ec)
            {
                std::string receivedPackage = std::string(recv_buffer_.data(), bytes_received);
                std::cout << "Received: " << receivedPackage << std::endl;

                //messageHandler->managePacket(receivedPackage);
            }
            else
            {
                std::cerr << "Error receiving: " << ec.message() << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(30));
            // Start listening for the next message
            start_receive();
        });
}

/*void Client::setConnected()
{
    connected = true;
}

bool Client::isConnected()
{
    return connected;
}*/