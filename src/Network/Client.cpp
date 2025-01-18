#include "Client.h"

Client::Client(boost::asio::io_context &io_context, const std::string &host, const std::string &port, std::unordered_map<std::string*, Npc*> *clients)
    : socket_(io_context), resolver_(io_context), server_endpoint_(*resolver_.resolve(udp::v4(), host, port).begin())
{
    this->clients = clients;

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
            {
                std::cerr << "Error sending: " << ec.message() << std::endl;
            }
            else
            {
                std::cout << "Sent " << bytes_sent << " bytes." << std::endl;
            }
        });
}

void Client::start_receive()
{
    /*if(!connected){
        
                Data data;
                data.id = 100;
                data.names.push_back("Hello");
                data.names.push_back("Steve");

                std::string bufferStr = data.serialize();

        this->send_message(bufferStr);
        connected = true;
    }*/

    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_),
        sender_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_received)
        {
            if (!ec)
            {
                std::string receivedPackage = std::string(recv_buffer_.data(), bytes_received);
                std::cout << "Received: " << receivedPackage << std::endl;

                Data receivedData;
                receivedData.deserialize(receivedPackage);

                if(receivedData.id == 102) {
                    bool playerExists = false;
                    std::string receivedKey = receivedData.names.at(0);

                    for (const auto& pair : *clients) {
                        std::string* key = pair.first; // Zeiger auf den Schlüssel
                        Npc* value = pair.second;     // Zeiger auf den Wert

                        if(*key == receivedKey){
                            playerExists = true;
                        }
                        // Verarbeitung der Schlüssel-Wert-Paare
                        std::cout << "Key: " << *key << ", Value: " << value << std::endl;
                    }

                    float x = std::stof(receivedData.names.at(1));
                    float z = std::stof(receivedData.names.at(2));
                    float y = std::stof(receivedData.names.at(3));


                    if(!playerExists) {
                        // Erstelle Schlüssel und Wert
                        std::string* key = &receivedKey;
                        Npc* value = new Npc(); // Npc ist ein Zeiger auf dein NPC-Objekt
                        value->setCurrentHealth(10);
                        value->setMaxHealth(10);
                        value->oCNpc->setVisualWithString("HUMANS.MDS");
                        value->oCNpc->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);

                        value->oCNpc->enableWithdCoords(x, z, y);

                        // Füge das Paar in die Map ein
                        clients->insert({key, value});
                    } else {
                        for (const auto& pair : *clients) {
                            std::string* key = pair.first; // Zeiger auf den Schlüssel
                            Npc* value = pair.second;     // Zeiger auf den Wert

                            if(*key == receivedKey){
                                value->setX(x);
                                value->setZ(z);
                                value->setY(y);
                                std::cout << "Found NPC\n";
                            }
                        }
                    }

                    std::string msg = "X: " + receivedData.names.at(1) + ", Z: " + receivedData.names.at(2) +", Y: " + receivedData.names.at(3);
                }
            }
            else
            {
                std::cerr << "Error receiving: " << ec.message() << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
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