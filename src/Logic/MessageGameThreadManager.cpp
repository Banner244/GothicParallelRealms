#include "MessageGameThreadManager.h"

MessageGameThreadManager::MessageGameThreadManager()
{
    clients = new std::unordered_map<std::string, Npc *>();
    messageHandler = new MessageHandler(clients);
}

void MessageGameThreadManager::setClientForHandler(Client &client)
{
    messageHandler->setClient(client);
}

void MessageGameThreadManager::addTask(std::string task)
{
    gameThreadTasks.push(task);
}

void MessageGameThreadManager::removeTask(std::string item)
{
    if (!gameThreadTasks.empty())
        gameThreadTasks.pop();
}
int count = 0;
Npc *mainPlayer;
Npc *npc;
void MessageGameThreadManager::processMessages()
{
    if (!gameThreadTasks.empty())
    {
        messageHandler->managePacket(gameThreadTasks.front());
        removeTask(gameThreadTasks.front());
    }

    /* ############## Custom Shit ################### */
    if (GetAsyncKeyState(VK_RSHIFT) < 0)
    {

        if (npc != nullptr)
        {
            int result = OCWorld::ShouldAddThisVobToBsp(npc);
            std::cout << "Prints: " << std::to_string(result) << "\n";
            
            //OCWorld::EnableVob(mainPlayer, npc);
            return;
        }

        mainPlayer = new Npc(ADDR_PLAYERBASE);
        ZVec3 tempPosition;
        mainPlayer->oCNpc->getPositionWorld(&tempPosition);

        // Npc *npc = new Npc();
        npc = new Npc();
        npc->setCurrentHealth(10);
        npc->setMaxHealth(10);
        npc->oCNpc->setVisualWithString("HUMANS.MDS");
        npc->oCNpc->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);
        npc->oCNpc->enable(&tempPosition);

        // Set same View direction as player
        zMAT4 matrix;
        mainPlayer->oCNpc->getTrafoModelNodeToWorld(&matrix, 0);
        npc->oCNpc->setTrafo(&matrix);

        zCModel *npcModel = new zCModel(npc->oCNpc->getModel());
        std::cout << "zCModel Addr: " << npcModel->getAddress() << "\n";

        // npcModel->startAniInt(342, 0); // ######################################
        // OCWorld::addVob(npc->oCNpc);
        // npc->oCNpc->setSleepingMode(0);
        // OCWorld::InsertInLists(npc->oCNpc);
        delete mainPlayer;
    }
}