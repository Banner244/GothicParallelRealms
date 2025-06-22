#include "GameThreadWorker.h"
#include <iomanip>

GameThreadWorker::GameThreadWorker()
{
    clients = new AsyncUnorderedMap<std::string, Npc *>();
    messageHandler = new MessageHandler(clients);
    pMainPlayer = new Npc(ADDR_PLAYERBASE);
}

GameThreadWorker::~GameThreadWorker()
{
    delete clients;
    delete messageHandler;
    delete pMainPlayer;
}

void GameThreadWorker::setClientForHandler(Client &client)
{
    messageHandler->setClient(client);
}

void GameThreadWorker::addTask(std::string task)
{
    gameThreadTasks.push(task);
}

void GameThreadWorker::removeTask()
{
    if (!gameThreadTasks.empty())
        gameThreadTasks.pop();
}

void GameThreadWorker::processMessages()
{
    if (!gameThreadTasks.empty())
    {
        messageHandler->managePacket(gameThreadTasks.front());
        removeTask();
    }
}
#include "../Wrapper/oCItem.h"
#include "../Wrapper/oCMsgWeapon.h"

Npc *npc;
void GameThreadWorker::checkGameState(){
    /* ## Checks if player is in range of an other player to render him ## */
    std::unordered_map<std::string, Npc*> copyOfClients = *clients->getUnorderedMap();

    for (const auto& pair : copyOfClients) {
        if (pMainPlayer->oCNpc->getDistanceToVob(pair.second->oCNpc) < 4500 && pair.second->oCNpc->getHomeWorld() == 0)
        {
            void *add = OCWorld::AddVob(pair.second->oCNpc);
            std::cout << "Add Address: " << add << "\n";
        }
    }

    /* ################ Custom Shit Here################# */
    if (GetAsyncKeyState(VK_RSHIFT) < 0)
    {
        std::cout << "--- ITEM STUFF ---- " << "\n";
        oCItem * armor = pMainPlayer->oCNpc->getEquippedArmor();
        oCItem * melee = pMainPlayer->oCNpc->getEquippedMeleeWeapon();
        oCItem * ranged = pMainPlayer->oCNpc->getEquippedRangedWeapon();
        
        std::cout << "Armor Address: " << armor << "\n";
        std::cout << "Armor Name: " << armor->getName() << "\n";
        zSTRING * zArmor = armor->getInstanceName();
        zSTRING * zMelee = melee->getInstanceName();
        zSTRING * zRanged = ranged->getInstanceName();
        std::cout << "zArmor Instance Name: " << zArmor->stdString() << "\n";
        std::cout << "zMelee Instance Name: " << zMelee->stdString() << "\n";
        std::cout << "zRanged Instance Name: " << zRanged->stdString() << "\n";

        oCItem * npcArmor = oCItem::CreateoCItem();
        npcArmor->setByScriptInstance(zArmor->c_str());
        oCItem * npcMelee = oCItem::CreateoCItem();
        npcMelee->setByScriptInstance(zMelee->c_str());
        oCItem * npcRanged = oCItem::CreateoCItem();
        npcRanged->setByScriptInstance(zRanged->c_str());
        //npcRanged->setFlag(4); //0x40000000, 0x800000
        //npcMelee->setFlag(2);

        std::cout << "CUSTOM Address : " << npcArmor << "\n";
        std::cout << "CUSTOM Name: " << npcArmor->getName() << "\n";

        std::cout << "CUSTOM Address : " << npcMelee << "\n";
        std::cout << "CUSTOM Name: " << npcMelee->getName() << "\n";

        std::cout << "CUSTOM Address : " << npcRanged << "\n";
        std::cout << "CUSTOM Name: " << npcRanged->getName() << "\n";
        std::cout << "---- -------- ---- " << "\n";


        /*oCItem * current = pMainPlayer->oCNpc->getWeapon();
        if(current) {
            std::cout << "current Address : " << current << "\n";
            std::cout << "current Name: " << current->getName() << "\n";
        } else {
            std::cout << "current EMPTY!\n";
        }*/

        if(npc == nullptr) {
            npc = new Npc();
            npc->setCurrentHealth(10);
            npc->setMaxHealth(10);
            npc->oCNpc->setVisualWithString("HUMANS.MDS");
            npc->oCNpc->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);
            //npc->oCNpc->setTalentValue(0, 10); // Strength
            //npc->oCNpc->setTalentValue(1, 10); //Dexterity
            npc->oCNpc->callVariable<int>(OCNpc::Offset::DEXTERITY) = 10;
            npc->oCNpc->callVariable<int>(OCNpc::Offset::STRENGTH) = 10;
            npc->oCNpc->enableWithdCoords(pMainPlayer->getX(), pMainPlayer->getZ(), pMainPlayer->getY());
            npc->setName("Steve");

            
            //npc->oCNpc->putInInv(npcRanged);
            //npc->oCNpc->putInInv(npcMelee);

            npc->oCNpc->equip(npcArmor);
            npc->oCNpc->equipItem(npcMelee);
            npc->oCNpc->equip(npcRanged);

            //npc->oCNpc->equipBestWeapon(2);
            //npc->oCNpc->equipBestWeapon(4);

            /*oCMsgWeapon * w = oCMsgWeapon::CreateoCMsgWeapon(4, 0, 0);
            int ka = npc->oCNpc->EV_DrawWeapon1(w);
            std::cout << "KA: " << std::to_string(ka) << "\n"; */


            /*nnpc->oCNpc->putInInv(npcArmor);
            npc->oCNpc->putInInv(npcRanged);
            npc->oCNpc->putInInv(npcMelee);*/


            //npc->oCNpc->equipItem(npcRanged);
        }
    }
}