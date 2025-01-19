#include "MessageHandler.h"

MessageHandler::MessageHandler(std::unordered_map<std::string*, Npc*> *clients) : clients(clients) {

}

void MessageHandler::managePacket(std::string stringPacket)
{

    Data receivedData;
    receivedData.deserialize(stringPacket);

    switch (receivedData.id)
    {
    case ServerPacket::serverHandshakeAccept:
        handleServerHandshakeAccept(receivedData);
        break;
    case ServerPacket::serverDistributePosition:
        handleServerDistributePosition(receivedData);
        break;

    default:
        std::cout << "\n\tWeird... Unknown Packet....\n";
    }
}

void MessageHandler::handleServerHandshakeAccept(Data data)
{
}

void MessageHandler::handleServerDistributePosition(Data data)
{
    std::cout << "handleServerDistributePosition\n"; 
    bool playerExists = false;
    std::string receivedKey = data.names.at(0);

    float x = std::stof(data.names.at(1));
    float z = std::stof(data.names.at(2));
    float y = std::stof(data.names.at(3));

    auto it = clients->find(&receivedKey);
    if (it != clients->end())
        playerExists = true;

    if (playerExists)
    {
        auto it = clients->find(&receivedKey);
        if (it != clients->end())
        {
            Npc *value = it->second; // Zeiger auf den Wert
            value->setX(x);
            value->setZ(z);
            value->setY(y);
            std::cout << "Found NPC\n";
        }
        return;
    }

    // Erstelle Schlüssel und Wert
    std::string *key = &receivedKey;
    Npc *value = new Npc(); // Npc ist ein Zeiger auf dein NPC-Objekt
    value->setCurrentHealth(10);
    value->setMaxHealth(10);
    value->oCNpc->setVisualWithString("HUMANS.MDS");
    value->oCNpc->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);

    value->oCNpc->enableWithdCoords(x, z, y);

    // Füge das Paar in die Map ein
    clients->insert({key, value});
}