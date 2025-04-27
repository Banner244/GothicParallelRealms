#include "MessageHandler.h"

MessageHandler::MessageHandler(std::unordered_map<std::string, Npc *> *pClients) : pClients(pClients)
{
}
void MessageHandler::setClient(Client &client)
{
    this->pClient = &client;
}

void MessageHandler::managePacket(std::string stringPacket)
{
    Packets::ServerPacket packetId = static_cast<Packets::ServerPacket>(PackagingSystem::ReadPacketId(stringPacket));

    switch (packetId)
    {
    case Packets::ServerPacket::serverHandshakeAccept:
        handleServerHandshakeAccept(stringPacket);
        break;
    case Packets::ServerPacket::serverRequestHeartbeat:
        handleServerRequestsHeartbeat(stringPacket);
        break;
    case Packets::ServerPacket::serverDistributePosition:
        handleServerDistributePosition(stringPacket);
        break;
    case Packets::ServerPacket::serverDistributeAnimations:
        handleServerDistributeAnimations(stringPacket);
        break;
    case Packets::ServerPacket::serverRemoveClient:
        handleServerRemoveClient(stringPacket);
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

void MessageHandler::handleServerRequestsHeartbeat(std::string &buffer)
{
    PackagingSystem packetAnim(Packets::ClientPacket::clientResponseHeartbeat);

    std::string bufferStr = packetAnim.serializePacket();
    this->pClient->send_message(bufferStr);
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
    auto it = pClients->find(receivedKey);
    if (it != pClients->end())
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

    // Creating a new Npc 
    Npc *value = new Npc();
    value->setCurrentHealth(10);
    value->setMaxHealth(10);
    value->oCNpc->setVisualWithString("HUMANS.MDS");
    value->oCNpc->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);

    value->oCNpc->enableWithdCoords(x, z, y);

    // New Client inserted
    pClients->insert({receivedKey, value});
}

void MessageHandler::handleServerDistributeAnimations(std::string &buffer)
{
    bool playerExists = false;
    std::string receivedKey = PackagingSystem::ReadItem<std::string>(buffer); // data.names.at(0);
    std::lock_guard<std::mutex> lock(clientsMutex);
    auto it = pClients->find(receivedKey);
    if (it != pClients->end())
        playerExists = true;

    if (!playerExists)
        return;

    Npc *value = it->second;
    DataStructures::LastAnimation npcLastAnim = value->getLastAnimation();
    DataStructures::LastAnimation npcNewAnim;
    zCModel *npcModel = new zCModel(value->oCNpc->getModel());

    int animCount = PackagingSystem::ReadItem<int>(buffer);
    npcNewAnim.animationCount = animCount;
    for (int i = 0; i < animCount; i++)
    {
        npcNewAnim.animationIds.push_back(PackagingSystem::ReadItem<int>(buffer));
    }

    for (auto &newId : npcNewAnim.animationIds) {
        npcModel->startAniInt(newId, 0);
    }

    for (auto &lastId : npcLastAnim.animationIds)
    {
        bool found = false;
        for (auto &newId : npcNewAnim.animationIds)
        {
            if(lastId == newId) {
                found = true;
            }
        }
        if(!found) {
            void *aniActive = npcModel->getActiveAni(lastId);
            if (aniActive)
                npcModel->stopAnimationInt(lastId);
        }
    }
}

/*##################### TODO:  TEST IF THIS WORKS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
void MessageHandler::handleServerRemoveClient(std::string &buffer)
{
    bool playerExists = false;
    std::string receivedKey = PackagingSystem::ReadItem<std::string>(buffer); // data.names.at(0);
    std::lock_guard<std::mutex> lock(clientsMutex);
    auto it = pClients->find(receivedKey);
    if (it != pClients->end())
    {
        OCWorld::RemoveVob(it->second->oCNpc);
        pClients->erase(receivedKey);
        std::cout << "Removed VOB\n";
    }
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