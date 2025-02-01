#include "Client.h"

Client::Client(boost::asio::io_context &io_context, const std::string &host, const std::string &port, MessageGameThreadManager *gameThreadManager)
    : socket_(io_context), resolver_(io_context), server_endpoint_(*resolver_.resolve(udp::v4(), host, port).begin())
{
    this->gameThreadManager = gameThreadManager;

    socket_.open(udp::v4());
    start_receive();
}

Client::~Client(){
    delete mainPlayer;
}

void Client::send_message(const std::string &message)
{
        try {
        std::size_t bytes_sent = socket_.send_to(
            boost::asio::buffer(message),
            server_endpoint_
        );

        std::cout << "Sent " << bytes_sent << " bytes." << std::endl;
    } catch (const boost::system::system_error& e) {
        std::cerr << "Error sending: " << e.what() << std::endl;
    }
    /*socket_.async_send_to(
        boost::asio::buffer(message),
        server_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_sent)
        {
            if (ec)
                std::cerr << "Error sending: " << ec.message() << std::endl;
            else
                std::cout << "Sent " << bytes_sent << " bytes." << std::endl;
        });*/
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

                this->gameThreadManager->addTask(receivedPackage);
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

void Client::sendPlayerPosition()
{
    zCModel npcModel(mainPlayer);
    zMAT4 matrix;
    mainPlayer->oCNpc->getTrafoModelNodeToWorld(&matrix, 0); // second param: Node specification (0 = no specific node)

    // get Rotation
    float yaw = atan2(matrix[0][2], matrix[0][0]);
    float pitch = asin(-matrix[0][1]);
    float roll = atan2(matrix[1][2], matrix[2][2]);

    Data data;
    data.id = 101;
    data.names.push_back(std::to_string(mainPlayer->getX()));
    data.names.push_back(std::to_string(mainPlayer->getZ()));
    data.names.push_back(std::to_string(mainPlayer->getY()));
    data.names.push_back(std::to_string(yaw));
    data.names.push_back(std::to_string(pitch));
    data.names.push_back(std::to_string(roll));
    data.names.push_back(std::to_string(npcModel.isAnimationActive("S_RUNL")));

    std::string bufferStr = data.serialize();
    this->send_message(bufferStr);
}

/*void Client::setConnected()
{
    connected = true;
}

bool Client::isConnected()
{
    return connected;
}*/