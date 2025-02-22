#include "MessageGameThreadManager.h"

MessageGameThreadManager::MessageGameThreadManager(){
    clients = new std::unordered_map<std::string, Npc*>();
    messageHandler = new MessageHandler(clients);
}

void MessageGameThreadManager::setClientForHandler(Client &client) {
    messageHandler->setClient(client);
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
int count = 0;
void MessageGameThreadManager::processMessages()
{
    if(!gameThreadTasks.empty()){
        //std::lock_guard<std::mutex> lock(clientsMutex); 
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
            //npc->oCNpc->setPhysicsEnabledRef(npc->oCNpc->getAddress(), 0);
            //npc->oCNpc->setStaticVobRef(npc->oCNpc->getAddress(), 0);
            zCModel *npcModel = new zCModel(npc->oCNpc->getModel()); 
            std::cout << "zCModel Addr: " << npcModel->getAddress() << "\n";

            //int id = npcModel->SearchAniIndex("S_RUNL");
            //std::cout << "id: " << id << "\n";


            //int numAnis = *(int*)((uintptr_t)npcModel + 0x38); // Anzahl aktiver Animationen
            //std::cout << "Active Animations: " << numAnis << std::endl;
/*std::cout << "\n";
            for (int i = 0; i < 700; i++) { 
                    void * aniActive = npcModel->getActiveAni(i);
                    if (!aniActive) continue;  // Sobald eine NULL kommt, abbrechen

                    int aniID = *(int*)((uintptr_t)aniActive + 0x4C);
                    float frame = *(float*)((uintptr_t)aniActive + 0x30);

                    std::cout << "Animation " << i << ": ID=" << aniID << ", Frame=" << frame << std::endl;
            }
std::cout << "\n";*/
            npcModel->startAniInt(342, 0);
            /*count++;*/


            /*void * aniFromID = npcModel->getAniFromAniID(8);
            npcModel->startAni(aniFromID, 0);*/

            //std::cout << "isAnimActive: " << npcModel->isAnimationActive("S_RUNL") << "\n";
            //npc->oCNpc->initHumanAI();
            
            //mainPlayer->oCNpc->move(mainPlayer->getX(), mainPlayer->getZ(), mainPlayer->getY()-1);
            //int ret = npc->oCNpc->applyOverlay("Humans_Militia.mds"); //(HUMANS_MILITIA.MDS),
            //npcModel->startAnimation("S_RUNL");

            //std::cout << "anim: " << ret << "\n";
            delete mainPlayer;
    }
}