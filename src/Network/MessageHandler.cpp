#include "MessageHandler.h"

MessageHandler::MessageHandler(AsyncUnorderedMap<std::string, Npc *> *pClients) : pClients(pClients)
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
    case Packets::ServerPacket::serverNewClientConnected:
        handleServerNewClientConnected(stringPacket);
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
    case Packets::ServerPacket::serverDistributeEquip:
        handleServerDistributeEquip(stringPacket);
        break;
    case Packets::ServerPacket::serverRemoveClient:
        handleServerRemoveClient(stringPacket);
        break;
    /*case Packets::ServerPacket::serverDistributeRotation:
        handleServerDistributeRotations(stringPacket);
        break;*/
    default:
        Async::PrintLn("\n\tWeird... Unknown Packet....\n");
    }
}

void MessageHandler::handleServerHandshakeAccept(std::string &buffer)
{
    std::string handshakeAnswer = PackagingSystem::ReadItem<std::string>(buffer);

    if (handshakeAnswer != "success")
    {
        return;
    }
    Async::PrintLn("HANDSHAKE SUCCESS!!");

    this->pClient->setConnected();
}

void MessageHandler::handleServerNewClientConnected(std::string &buffer)
{
    std::string receivedKey = PackagingSystem::ReadItem<std::string>(buffer);
    std::string name = PackagingSystem::ReadItem<std::string>(buffer);
    float x = PackagingSystem::ReadItem<float>(buffer);
    float z = PackagingSystem::ReadItem<float>(buffer);
    float y = PackagingSystem::ReadItem<float>(buffer);

    float yaw = PackagingSystem::ReadItem<float>(buffer);
    float pitch = PackagingSystem::ReadItem<float>(buffer);
    float roll = PackagingSystem::ReadItem<float>(buffer);

    std::string melee = PackagingSystem::ReadItem<std::string>(buffer);
    std::string ranged = PackagingSystem::ReadItem<std::string>(buffer);
    std::string armor = PackagingSystem::ReadItem<std::string>(buffer);

    // Creating a new Npc
    Npc *value = new Npc();
    value->setCurrentHealth(10);
    value->setMaxHealth(10);
    value->oCNpc->setVisualWithString("HUMANS.MDS");
    value->oCNpc->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);
    value->oCNpc->callVariable<int>(OCNpc::Offset::DEXTERITY) = 50;
    value->oCNpc->callVariable<int>(OCNpc::Offset::STRENGTH) = 50;
    value->setName(name);

    zMAT4 matrix;
    value->oCNpc->getTrafoModelNodeToWorld(&matrix, 0);

    matrix.MakeRotationY(yaw);
    value->oCNpc->setTrafo(&matrix);

    value->setX(x);
    value->setZ(z);
    value->setY(y);
    value->oCNpc->enableWithdCoords(x, z, y);




    PackagingSystem internEquipAnswer(Packets::ServerPacket::serverDistributeEquip);
    internEquipAnswer.addString(receivedKey);
    internEquipAnswer.addString(melee);
    internEquipAnswer.addString(ranged);
    internEquipAnswer.addString(armor);
    std::string internEquipAnswertemp = internEquipAnswer.serializePacket();
    PackagingSystem::ReadPacketId(internEquipAnswertemp);// have to remove it
    handleServerDistributeEquip(internEquipAnswertemp);


    // New Client inserted
    pClients->append(receivedKey, value);
}

void MessageHandler::handleServerRequestsHeartbeat(std::string &buffer)
{
    PackagingSystem packetAnim(Packets::ClientPacket::clientResponseHeartbeat);

    std::string bufferStr = packetAnim.serializePacket();
    this->pClient->send_message(bufferStr);
}

void MessageHandler::handleServerDistributePosition(std::string &buffer)
{
    std::string receivedKey = PackagingSystem::ReadItem<std::string>(buffer);
    float x = PackagingSystem::ReadItem<float>(buffer);
    float z = PackagingSystem::ReadItem<float>(buffer);
    float y = PackagingSystem::ReadItem<float>(buffer);

    float yaw = PackagingSystem::ReadItem<float>(buffer);
    float pitch = PackagingSystem::ReadItem<float>(buffer);
    float roll = PackagingSystem::ReadItem<float>(buffer);

    auto it = pClients->find(receivedKey);
    if (!it)
        return;

    Npc *value = it.value();
    zMAT4 matrix;
    value->oCNpc->getTrafoModelNodeToWorld(&matrix, 0);

    matrix.MakeRotationY(yaw);
    value->oCNpc->setTrafo(&matrix);

    value->setX(x);
    value->setZ(z);
    value->setY(y);
}

void MessageHandler::handleServerDistributeAnimations(std::string &buffer)
{
    std::string receivedKey = PackagingSystem::ReadItem<std::string>(buffer);

    auto it = pClients->find(receivedKey);
    if (!it)
    {
        return;
    }

    Npc *value = it.value();
    DataStructures::LastAnimation npcLastAnim = value->getLastAnimation();
    DataStructures::LastAnimation npcNewAnim;
    zCModel *npcModel = new zCModel(value->oCNpc->getModel());

    int animCount = PackagingSystem::ReadItem<int>(buffer);
    npcNewAnim.animationCount = animCount;
    for (int i = 0; i < animCount; i++)
    {
        npcNewAnim.animationIds.push_back(PackagingSystem::ReadItem<int>(buffer));
    }

    for (auto &newId : npcNewAnim.animationIds)
    {
        npcModel->startAniInt(newId, 0);
    }

    for (auto &lastId : npcLastAnim.animationIds)
    {
        bool found = false;
        for (auto &newId : npcNewAnim.animationIds)
        {
            if (lastId == newId)
            {
                found = true;
            }
        }
        if (!found)
        {
            void *aniActive = npcModel->getActiveAni(lastId);
            if (aniActive)
                npcModel->stopAnimationInt(lastId);
        }
    }
}

void MessageHandler::handleServerDistributeEquip(std::string &buffer)
{
    std::string receivedKey = PackagingSystem::ReadItem<std::string>(buffer);
    std::string melee = PackagingSystem::ReadItem<std::string>(buffer);
    std::string ranged = PackagingSystem::ReadItem<std::string>(buffer);
    std::string armor = PackagingSystem::ReadItem<std::string>(buffer);


    auto it = pClients->find(receivedKey);
    if (!it)
    {
        return;
    }

    Npc *value = it.value();

    DataStructures::LastEquip currentEquip = value->getLastEquip();


    if(armor == "" && currentEquip.armorInstanceName != "") {
        value->oCNpc->unequipItem(value->oCNpc->getEquippedArmor());
    } else if(armor != "" ){
        if(currentEquip.armorInstanceName != "") {
            value->oCNpc->unequipItem(value->oCNpc->getEquippedArmor());
        }
        oCItem * newArmor = oCItem::CreateoCItem();
        newArmor->setByScriptInstance(armor.c_str());
        value->oCNpc->equipArmor(newArmor);
    }

    if(ranged == "" && currentEquip.rangedWeaponInstanceName != "") {
        value->oCNpc->unequipItem(value->oCNpc->getEquippedRangedWeapon());
    } else if(ranged != "" ){
        if(currentEquip.rangedWeaponInstanceName != "") {
            value->oCNpc->unequipItem(value->oCNpc->getEquippedRangedWeapon());
        }
        oCItem * newRanged = oCItem::CreateoCItem();
        newRanged->setByScriptInstance(ranged.c_str());
        value->oCNpc->equip(newRanged);
    }

    if(melee == "" && currentEquip.meleeWeaponInstanceName != "") {
        value->oCNpc->unequipItem(value->oCNpc->getEquippedMeleeWeapon());
    } else if(melee != "" ){
        if(currentEquip.meleeWeaponInstanceName != "") {
            value->oCNpc->unequipItem(value->oCNpc->getEquippedMeleeWeapon());
        }
        oCItem * newMelee = oCItem::CreateoCItem();
        newMelee->setByScriptInstance(melee.c_str());
        value->oCNpc->equipWeapon(newMelee);
    }
}

void MessageHandler::handleServerRemoveClient(std::string &buffer)
{
    std::string receivedKey = PackagingSystem::ReadItem<std::string>(buffer); // data.names.at(0);

    auto it = pClients->find(receivedKey);
    if (!it)
        return;

    OCWorld::RemoveVob(it.value());
    pClients->remove(receivedKey);
    Async::PrintLn("Removed VOB\n");
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