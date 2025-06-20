#include "Client.h"

Client::Client(boost::asio::io_context &io_context, const std::string &username, const std::string &host, const std::string &port, GameThreadWorker *gameThreadWorker)
    : socket_(io_context), resolver_(io_context), username(username), server_endpoint_(*resolver_.resolve(udp::v4(), host, port).begin())
{
    this->gameThreadWorker = gameThreadWorker;

    socket_.open(udp::v4());
    start_receive();
    gameThreadWorker->setClientForHandler(*this);
}

Client::~Client()
{
    delete mainPlayer;
    delete gameThreadWorker;
}

Npc * Client::getMainPlayer(){
    return mainPlayer;
}

void Client::send_message(const std::string &message)
{
    auto message_ptr = std::make_shared<std::string>(message); // keep the message in the memory
    std::cout << "Packet " << *message_ptr << std::endl;
    socket_.async_send_to(
        boost::asio::buffer(*message_ptr),
        server_endpoint_,
        [this, message_ptr](boost::system::error_code ec, std::size_t bytes_sent) //
        {
            if (ec)
                std::cerr << "Error sending: " << ec.message() << std::endl;
            else {
                std::cout << "Sent " << bytes_sent << " bytes." << std::endl;
            }
                
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
                this->gameThreadWorker->addTask(receivedPackage);
            }
            else
            {
                std::cerr << "Error receiving: " << ec.message() << std::endl;
            }
            // Nächstes Paket empfangen
            start_receive();
        });
}

void Client::setConnected() {
    this->connected = true;
}

const bool Client::isConnected() const {
    return connected;
}

void Client::sendHandshakeRequest() {
    PackagingSystem packetHandshake(Packets::ClientPacket::clientHandshakeRequest);
    packetHandshake.addString(this->username);

    DataStructures::LastPosition lasPos = mainPlayer->getLastPosition();
    packetHandshake.addFloatPointNumber(lasPos.x + 90, 2);
    packetHandshake.addFloatPointNumber(lasPos.z, 2);
    packetHandshake.addFloatPointNumber(lasPos.y + 90, 2);

    packetHandshake.addFloatPointNumber(lasPos.yaw, 2);
    packetHandshake.addFloatPointNumber(lasPos.pitch, 2);
    packetHandshake.addFloatPointNumber(lasPos.roll, 2);

    DataStructures::LastEquip lastEquip =  mainPlayer->getLastEquip();
    packetHandshake.addString(lastEquip.meleeWeaponInstanceName);
    packetHandshake.addString(lastEquip.rangedWeaponInstanceName);
    packetHandshake.addString(lastEquip.armorInstanceName);

    std::string bufferStr = packetHandshake.serializePacket();
    this->send_message(bufferStr);
}

void Client::sendPlayerPosition()
{
    DataStructures::LastPosition lasPos = mainPlayer->getLastPosition();

    PackagingSystem packetAnim(Packets::ClientPacket::clientSharePosition);
    packetAnim.addFloatPointNumber(lasPos.x + 90, 2);
    packetAnim.addFloatPointNumber(lasPos.z, 2);
    packetAnim.addFloatPointNumber(lasPos.y + 90, 2);

    packetAnim.addFloatPointNumber(lasPos.yaw, 2);
    packetAnim.addFloatPointNumber(lasPos.pitch, 2);
    packetAnim.addFloatPointNumber(lasPos.roll, 2);


    std::string bufferStr = packetAnim.serializePacket();
    this->send_message(bufferStr);
}

void Client::sendPlayerAnimation()
{
    DataStructures::LastAnimation lastAnim =  mainPlayer->getLastAnimation();

    PackagingSystem packetAnim(Packets::ClientPacket::clientShareAnimations);
    packetAnim.addInt(lastAnim.animationCount);

    for(const auto &id : lastAnim.animationIds) {
        packetAnim.addInt(id);
    }

    std::string bufferStr = packetAnim.serializePacket();
    this->send_message(bufferStr);
}

void Client::sendPlayerEquip()
{
    DataStructures::LastEquip lastEquip =  mainPlayer->getLastEquip();

    PackagingSystem packetEquip(Packets::ClientPacket::clientShareEquip);
    
    packetEquip.addString(lastEquip.meleeWeaponInstanceName);
    packetEquip.addString(lastEquip.rangedWeaponInstanceName);
    packetEquip.addString(lastEquip.armorInstanceName);

    std::string bufferStr = packetEquip.serializePacket();
    this->send_message(bufferStr);
}

void Client::sendPlayerRotation() {
    /*Data data;
    data.id = ClientPacket::clientShareRotation;

    DataStructures::LastRotation lastRot =  mainPlayer->getLastRotation();

    data.names.push_back(std::to_string(lastRot.yaw));
    data.names.push_back(std::to_string(lastRot.pitch));
    data.names.push_back(std::to_string(lastRot.roll));

    std::string bufferStr = data.serialize();
    this->send_message(bufferStr);*/
}

/*void Client::setConnected()
{
    connected = true;
}

bool Client::isConnected()
{
    return connected;
}*/