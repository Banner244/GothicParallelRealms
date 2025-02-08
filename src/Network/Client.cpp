#include "Client.h"

struct AnimationInformation {
    int id;
    float frame;
};

Client::Client(boost::asio::io_context &io_context, const std::string &host, const std::string &port, MessageGameThreadManager *gameThreadManager)
    : socket_(io_context), resolver_(io_context), server_endpoint_(*resolver_.resolve(udp::v4(), host, port).begin())
{
    this->gameThreadManager = gameThreadManager;

    socket_.open(udp::v4());
    start_receive();
}

Client::~Client()
{
    delete mainPlayer;
    delete gameThreadManager;
}

void Client::send_message(const std::string &message)
{
    auto message_ptr = std::make_shared<std::string>(message); // keep the message in the memory

    socket_.async_send_to(
        boost::asio::buffer(*message_ptr),
        server_endpoint_,
        [this, message_ptr](boost::system::error_code ec, std::size_t bytes_sent) //
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
                if (bytes_received == recv_buffer_.size()) {
                    std::cerr << "Warnung: Möglicherweise abgeschnittenes Paket!" << std::endl;
                }

                std::string receivedPackage(recv_buffer_.data(), bytes_received);
                std::cout << "Received: " << receivedPackage << std::endl;
                
                // Buffer leeren
                std::fill(recv_buffer_.begin(), recv_buffer_.end(), 0);

                // Paket verarbeiten
                this->gameThreadManager->addTask(receivedPackage);
            }
            else
            {
                std::cerr << "Error receiving: " << ec.message() << std::endl;
            }
            // Nächstes Paket empfangen
            start_receive();
        });
}

void Client::sendPlayerPosition()
{
    zCModel *npcModel = new zCModel(mainPlayer->oCNpc->getModel());
    zMAT4 matrix;
    mainPlayer->oCNpc->getTrafoModelNodeToWorld(&matrix, 0); // second param: Node specification (0 = no specific node)

    std::string x = std::to_string((mainPlayer->getX() + 90));
    std::string y = std::to_string((mainPlayer->getY() + 90));

    // get Rotation
    float yaw = atan2(matrix[0][2], matrix[0][0]);
    float pitch = asin(-matrix[0][1]);
    float roll = atan2(matrix[1][2], matrix[2][2]);

    Data data;
    data.id = ClientPacket::clientSharePosition;
    data.names.push_back(x);
    data.names.push_back(std::to_string(mainPlayer->getZ()));
    data.names.push_back(y);
    data.names.push_back(std::to_string(yaw));
    data.names.push_back(std::to_string(pitch));
    data.names.push_back(std::to_string(roll));
    data.names.push_back(std::to_string(npcModel->isAnimationActive("S_RUNL")));

    std::string bufferStr = data.serialize();
    this->send_message(bufferStr);
}

void Client::sendPlayerAnimation()
{
    zCModel *npcModel = new zCModel(mainPlayer->oCNpc->getModel());

    
    //std::vector<AnimationInformation> animList;
    auto animList = std::make_shared<std::vector<AnimationInformation>>();


    for (int i = 0; i < 550; i++)
    {
        void *aniActive = npcModel->getActiveAni(i);
        if (!aniActive)
            continue; // Sobald eine NULL kommt, abbrechen


        //int aniID = *(int *)((uintptr_t)aniActive + 0x4C);
        float frame = *(float *)((uintptr_t)aniActive + 0x30);

        AnimationInformation animInfo;
        animInfo.id = i;
        animInfo.frame = frame;

        animList->push_back(animInfo);
        break;
        //std::cout << "Animation " << i << ": ID=" << aniID << ", Frame=" << frame << std::endl;
    }

    int animCount = animList->size();

    Data data;
    data.id = ClientPacket::clientShareAnimations;
    data.names.push_back( std::to_string(animCount));
    
    for(int i = 0; i< animCount; i++) {
        data.names.push_back(std::to_string(animList->at(i).id));
        //data.names.push_back(std::to_string(animList.at(i).frame));
    }

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