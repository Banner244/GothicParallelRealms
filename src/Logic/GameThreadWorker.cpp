#include "GameThreadWorker.h"

GameThreadWorker::GameThreadWorker()
{
    clients = new std::unordered_map<std::string, Npc *>();
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
//Npc *npc;
void GameThreadWorker::checkGameState(){
    // Checks if player is in range of an other player to render him
    for (const auto& pair : *clients) {
        if (pMainPlayer->oCNpc->getDistanceToVob(pair.second->oCNpc) < 4500 && pair.second->oCNpc->getHomeWorld() == 0)
        {
            void *add = OCWorld::AddVob(pair.second->oCNpc);
            std::cout << "Add Address: " << add << "\n";
        }
    }

    /* ################ Custom Shit Here################# */
    if (GetAsyncKeyState(VK_RSHIFT) < 0)
    {
        zCModel *npcModel = new zCModel(pMainPlayer->oCNpc->getModel());
        std::cout << "zCModel Addr: " << npcModel->getAddress() << "\n";
        npcModel->showAniList(0);

        /*
        ZVec3 tempPosition;
        pMainPlayer->oCNpc->getPositionWorld(&tempPosition);
        // Npc *npc = new Npc();
        npc = new Npc();
        npc->setCurrentHealth(10);
        npc->setMaxHealth(10);
        npc->oCNpc->setVisualWithString("HUMANS.MDS");
        npc->oCNpc->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);
        npc->oCNpc->enable(&tempPosition);

        // Set same View direction as player
        zMAT4 matrix;
        pMainPlayer->oCNpc->getTrafoModelNodeToWorld(&matrix, 0);
        npc->oCNpc->setTrafo(&matrix);

        zCModel *npcModel = new zCModel(npc->oCNpc->getModel());
        std::cout << "zCModel Addr: " << npcModel->getAddress() << "\n";*/

    }
}