#include "MessageGameThreadManager.h"

MessageGameThreadManager::MessageGameThreadManager(){
    clients = new std::unordered_map<std::string, Npc*>();
    messageHandler = new MessageHandler(clients);
}

void MessageGameThreadManager::addTask(std::string task)
{
    gameThreadTasks.push_back(task);
}

void MessageGameThreadManager::removeTask(std::vector<std::string>::iterator it)
{
    gameThreadTasks.erase(it);
}

void MessageGameThreadManager::processMessages()
{
    std::vector<std::string>::iterator firstTask = gameThreadTasks.begin();

    if (firstTask == gameThreadTasks.end()) {
        std::cout << "no messages\n";
        return;
    }

    messageHandler->managePacket(*firstTask);


    /*if (GetKeyState(VK_HOME) < 0)
    {
        Npc *mainPlayer = new Npc(ADDR_PLAYERBASE);
        ZVec3 tempPosition;
        mainPlayer->oCNpc->getPositionWorld(&tempPosition);
        std::cout << tempPosition.getPos() << std::endl;

        Npc *npc = new Npc();
        npc->setCurrentHealth(10);
        npc->setMaxHealth(10);
        npc->oCNpc->setVisualWithString("HUMANS.MDS");
        npc->oCNpc->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);

        npc->oCNpc->enable(&tempPosition);

        zMAT4 matrix;
        mainPlayer->oCNpc->getTrafoModelNodeToWorld(&matrix, 0);
        npc->oCNpc->setTrafo(&matrix);
    }*/
}