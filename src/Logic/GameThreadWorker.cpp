#include "GameThreadWorker.h"

GameThreadWorker::GameThreadWorker()
{
    clients = new std::unordered_map<std::string, Npc *>();
    messageHandler = new MessageHandler(clients);
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

int count = 0;
Npc *mainPlayer;
Npc *npc;

void GameThreadWorker::checkGameState(){
    if(mainPlayer == nullptr) {
        mainPlayer = new Npc(ADDR_PLAYERBASE);
    }
    // Checks if player is in range of an other player to render him
    for (const auto& pair : *clients) {
        if (mainPlayer->oCNpc->getDistanceToVob(pair.second->oCNpc) < 4500 && pair.second->oCNpc->getHomeWorld() == 0)
        {
            
            void *add = OCWorld::AddVob(pair.second->oCNpc);
            std::cout << "Add Address: " << add << "\n";
        }
    }

    /* ################ Custom Shit Here################# */
    if (GetAsyncKeyState(VK_RSHIFT) < 0)
    {
        // std::cout << "Pressed Button!\n";
        if (npc != nullptr)
        {
            //OCWorld::EnableVob(mainPlayer->oCNpc, npc->oCNpc);
            //mainPlayer->oCNpc->insertInVobList(npc->oCNpc);

            //OCWorld::InsertInLists(npc->oCNpc);
            std::cout << "Distance to NPC: " << std::to_string(mainPlayer->oCNpc->getDistanceToVob(npc->oCNpc)) << "\n";

            if(npc->oCNpc != nullptr ) {
                std::cout << "World Address: " << OCWorld::GetOCWorldAddress() << "\n";
                

                //OCWorld::VobAddedToWorld(npc->oCNpc);
                //npc->oCNpc->addVobToWorld_CorrectParentDependencies();
                //void * add = OCWorld::AddVob(npc->oCNpc);
                //std::cout << "Add Address: " << add << "\n";
            } else {
                std::cout << "NPC is NULL" << "\n";
            }

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

        // delete mainPlayer;
    }
}