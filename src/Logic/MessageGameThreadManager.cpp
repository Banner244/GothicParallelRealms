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
    if(!gameThreadTasks.empty())
        gameThreadTasks.erase(it);
}

void MessageGameThreadManager::processMessages()
{
    if(!gameThreadTasks.empty()){
        std::vector<std::string>::iterator firstTask = gameThreadTasks.begin();

        if (firstTask == gameThreadTasks.end()) 
            return;
        
        messageHandler->managePacket(*firstTask);
        removeTask(firstTask);
    }

    if (GetAsyncKeyState(VK_RSHIFT) < 0)
    {
            Npc *mainPlayer = new Npc(ADDR_PLAYERBASE);
            ZVec3 tempPosition;
            mainPlayer->oCNpc->getPositionWorld(&tempPosition);

            Npc *npc = new Npc();
            npc->setCurrentHealth(10);
            npc->setMaxHealth(10);
            npc->oCNpc->setVisualWithString("HUMANS.MDS");
            npc->oCNpc->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);
            npc->oCNpc->enable(&tempPosition);

            // Set same View direction as player
            zMAT4 matrix;
            mainPlayer->oCNpc->getTrafoModelNodeToWorld(&matrix, 0); 
            npc->oCNpc->setTrafo(&matrix);
            /*npc->oCNpc->beginMovement();
            npc->oCNpc->move(mainPlayer->getX()+5, mainPlayer->getZ(), mainPlayer->getY());*/
            npc->oCNpc->setPhysicsEnabledRef(npc->oCNpc->getAddress(), 0);
            //npc->oCNpc->setStaticVobRef(npc->oCNpc->getAddress(), 0);
            zCModel *npcModel = new zCModel(npc->oCNpc->getModel()); 
            std::cout << "zCModel Addr: " << npcModel->pThis << "\n";
            
            int ret = npc->oCNpc->applyOverlay("HUMANS_FLEE.MDS"); //(HUMANS_MILITIA.MDS),
            //npcModel->startAnimation("S_RUNL");

            std::cout << "anim: " << ret << "\n";
            delete mainPlayer;
    }
}