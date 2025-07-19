#include "ClientGameMapping.h"

ClientGameMapping::ClientGameMapping(AsyncUnorderedMap<std::string, Npc *> *pClients)
    : pClients(pClients)
{
}

void ClientGameMapping::manageClientsInSync()
{
    syncAnimation();
}

void ClientGameMapping::syncAnimation()
{
    /*std::lock_guard<std::mutex> lock(pClients->getMutex());
    for (auto it = pClients->getUnorderedMap()->begin(); it != pClients->getUnorderedMap()->end(); ++it)
    {
        std::unique_ptr<zCModel> npcModel = std::make_unique<zCModel>(it->second->oCNpc->getModel());
        //zCModel* npcModel = reinterpret_cast<zCModel*>(it->second->oCNpc->getModel());

        auto networkAnim = it->second->networkState.animation;
        auto lastAnim = it->second->getLastAnimation();

        if (!lastAnim.isSame(networkAnim))
        {
            std::cout << "IS NOT SAME ANIM!!!!!!!!!!!! STARTING\n";
            for (auto &newId : networkAnim.animationIds)
            {
                npcModel->startAniInt(newId, 0);
            }
        }
    }*/
}