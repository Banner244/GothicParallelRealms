#include "GameThreadWorker.h"
#include <iomanip>

GameThreadWorker::GameThreadWorker(Client &client)
{
    messageHandler = std::make_unique<MessageHandler>(&clients, client);
    pMainPlayer = std::make_unique<Npc>(ADDR_PLAYERBASE);

    mapping = std::make_unique<ClientGameMapping>(&clients);
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

void GameThreadWorker::checkGameState(){
    /* ## Checks if player is in range of an other player to render him ## */
    std::unordered_map<std::string, Npc*> copyOfClients = *clients.getUnorderedMap();

    for (const auto& pair : copyOfClients) {
        if (pMainPlayer->oCNpc->getDistanceToVob(pair.second->oCNpc) < 4500 && pair.second->oCNpc->getHomeWorld() == 0)
        {
            void *add = OCWorld::AddVob(pair.second->oCNpc);
            std::cout << "Add Address: " << add << "\n";
        }
    }

    /* ## Checks if clients are in sync with there acions ## */
    mapping->manageClientsInSync();

}