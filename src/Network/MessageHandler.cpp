#include "MessageHandler.h"

MessageHandler::MessageHandler(std::unordered_map<std::string, Npc *> *clients) : clients(clients)
{
}

void MessageHandler::managePacket(std::string stringPacket)
{
    /*Data receivedData;
    receivedData.deserialize(stringPacket);*/
    Packets::ServerPacket packetId = static_cast<Packets::ServerPacket>(PackagingSystem::ReadPacketId(stringPacket));

    switch (packetId)
    {
    case Packets::ServerPacket::serverHandshakeAccept:
        handleServerHandshakeAccept(stringPacket);
        break;
    case Packets::ServerPacket::serverDistributePosition:
        handleServerDistributePosition(stringPacket);
        break;
    case Packets::ServerPacket::serverDistributeAnimations:
        handleServerDistributeAnimations(stringPacket);
        break;
    /*case Packets::ServerPacket::serverDistributeRotation:
        handleServerDistributeRotations(stringPacket);
        break;*/
    default:
        std::cout << "\n\tWeird... Unknown Packet....\n";
    }
}

void MessageHandler::handleServerHandshakeAccept(std::string &buffer)
{
    
}

void MessageHandler::handleServerDistributePosition(std::string &buffer)
{
    bool playerExists = false;
    std::string receivedKey = PackagingSystem::ReadItem<std::string>(buffer);
    float x = PackagingSystem::ReadItem<float>(buffer);
    float z = PackagingSystem::ReadItem<float>(buffer);
    float y = PackagingSystem::ReadItem<float>(buffer);

    float yaw = PackagingSystem::ReadItem<float>(buffer);
    float pitch = PackagingSystem::ReadItem<float>(buffer);
    float roll = PackagingSystem::ReadItem<float>(buffer);

    std::lock_guard<std::mutex> lock(clientsMutex);
    auto it = clients->find(receivedKey);
    if (it != clients->end())
        playerExists = true;

    if (playerExists)
    {
        Npc *value = it->second;
        zMAT4 matrix;
        value->oCNpc->getTrafoModelNodeToWorld(&matrix, 0);

        matrix.MakeRotationY(yaw);
        value->oCNpc->setTrafo(&matrix);

        value->setX(x);
        value->setZ(z);
        value->setY(y);
        return;
    }

    Npc *value = new Npc(); // Npc ist ein Zeiger auf dein NPC-Objekt
    value->setCurrentHealth(10);
    value->setMaxHealth(10);
    value->oCNpc->setVisualWithString("HUMANS.MDS");
    value->oCNpc->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);

    value->oCNpc->enableWithdCoords(x, z, y);

    // Füge das Paar in die Map ein
    clients->insert({receivedKey, value});
}

void MessageHandler::handleServerDistributeAnimations(std::string &buffer)
{
    bool playerExists = false;
    std::string receivedKey = PackagingSystem::ReadItem<std::string>(buffer); //data.names.at(0);
    std::lock_guard<std::mutex> lock(clientsMutex);
    auto it = clients->find(receivedKey);
    if (it != clients->end())
        playerExists = true;

    if (!playerExists)
        return;

    Npc *value = it->second;
    zCModel *npcModel = new zCModel(value->oCNpc->getModel());

    int animID = PackagingSystem::ReadItem<int>(buffer);


    for(int i = 0; i < 550; i++){
        void *aniActive = npcModel->getActiveAni(i);
        if (aniActive)
            npcModel->stopAnimationInt(i);
    }

    //void *aniActive = npcModel->getActiveAni(animID);
    //if (!aniActive)
    npcModel->startAniInt(animID, 0);
    /*int animCount = std::stoi(data.names.at(1));
    if (animCount != 0)
    {
        int animID = std::stoi(data.names.at(2));

        void *aniActive = npcModel->getActiveAni(animID);
        if (!aniActive)
            npcModel->startAniInt(animID, 0);
    }*/
}

void MessageHandler::handleServerDistributeRotations(std::string &buffer)
{
    /*bool playerExists = false;
    std::string receivedKey = PackagingSystem::ReadItem<std::string>(buffer);
    std::lock_guard<std::mutex> lock(clientsMutex);

    auto it = clients->find(receivedKey);
    if (it != clients->end())
        playerExists = true;

    if (!playerExists)
        return;

    Npc *value = it->second;

    float yaw = std::stof(data.names.at(1));
    float pitch = std::stof(data.names.at(2));
    float roll = std::stof(data.names.at(3));

    zMAT4 matrix;
    value->oCNpc->getTrafoModelNodeToWorld(&matrix, 0);

    matrix.MakeRotationY(yaw);


    value->oCNpc->setTrafo(&matrix);*/
}