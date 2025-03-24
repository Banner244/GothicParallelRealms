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

void MessageGameThreadManager::removeTask()
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
        removeTask();
    }

    /* ############## Custom Shit ################### */
    if (GetAsyncKeyState(VK_RSHIFT) < 0)
    {
        //std::cout << "Pressed Button!\n";
        if (npc != nullptr)
        {
            /*std::cout << "World Address: " << OCWorld::GetOCWorldAddress() << std::endl;
            //OCWorld::InsertInLists(npc->oCNpc);
            void *add = OCWorld::AddVob(npc->oCNpc);
            std::cout << "Add Address: " << add << "\n";*/

            //npc->oCNpc->setSleeping(1);
            //npc->oCNpc->setSleepingMode(0);

            /*if(npc->oCNpc != nullptr ) {
                void * add = OCWorld::AddVob(npc->oCNpc->getAddress());
                std::cout << "Add Address: " << add << "\n";
            } else {
                std::cout << "NPC is NULL" << "\n";
            }*/

            //npc->oCNpc->setVobPresentName("Steve");
            //OCWorld::PrintStatus();
            //std::cout << "Tree Address: " << OCWorld::GetOCWorldGlobalVobTree() << std::endl;
            

            //void * tree = nullptr;
            //OCWorld::PrintGlobalVobTree(tree, 0);
            //std::cout << "Tree Address: " << tree << std::endl;

/*
            std::cout << "VobHashInd NPC: " << std::to_string( OCWorld::GetVobHashIndex(npc->oCNpc)) << std::endl;
            OCWorld::PrintStatus();*/
            return;
        }

        

        mainPlayer = new Npc(ADDR_PLAYERBASE);
        /*ZVec3 tempPosition;
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
        std::cout << "zCModel Addr: " << npcModel->getAddress() << "\n";*/

        // ################### RENDER FIX TESTS ###################
        //npc->oCNpc->setSleepingMode(0); // Works kinda... it sleeps
        //npc->oCNpc->addRefVobSubtree(OCWorld::GetOCWorldGlobalVobTree());
        //OCWorld::InserIntoGlobalVobTree(npc->oCNpc);


        /*void * tree = OCWorld::AddVob(npc->oCNpc);
        std::cout << "Tree: " << tree << "\n"; /// WHY 0000000F ???????????????????
        npc->oCNpc->addRefVobSubtree(tree);

        using _CountNodes = int(__thiscall *)(void *pThis);
        _CountNodes countNodes = (_CountNodes)(0x5f9ea0);
        int nodes= countNodes(tree);

        std::cout << "Nodes: " << std::to_string(nodes) << "\n";*/
        //OCWorld::RemoveVob(npc->oCNpc);
        //std::cout << "Removed Vob..." << "\n";
        delete mainPlayer;
    }
}