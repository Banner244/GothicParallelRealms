#include "GameThreadWorker.h"

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
//Npc *npc;
//int *ii = new int;
void GameThreadWorker::checkGameState(){
    // Checks if player is in range of an other player to render him
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
        std::cout << "# PRINTING "   << "\n";
        zSTRING * str = new zSTRING("");
        str = pMainPlayer->oCNpc->getName(0);
        std::cout << "NAME: " << str->getStr() << "\n";
    }
}