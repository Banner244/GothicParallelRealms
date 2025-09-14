#pragma once

#include <iostream>
#include <unordered_map>
#include <queue>

#include "../Models/GlobalFunctions.h"

#include "../Wrapper/OCNpc.h"
#include "../Wrapper/zCModel.h"
#include "../Wrapper/OCWorld.h"

#include "../Network/Client.h"
#include "../Network/MessageHandler.h"

#include "ClientGameMapping.h"

#include "../common/src/Async/AsyncUnorderedMap.h"
#include "../Wrapper/oCItem.h"
#include "../Wrapper/oCMsgWeapon.h"


class Client;
class Npc;
class MessageHandler;

class Playground {

    public:
        Playground(){
            pMainPlayer = std::make_unique<Npc>(ADDR_PLAYERBASE);
        }

        void doThing(){
                /* ################ Custom Shit Here################# */
            if (GetAsyncKeyState(VK_RSHIFT) < 0)
            {

                if(npc == nullptr) {
                    npc = new Npc();
                    npc->setCurrentHealth(10);
                    npc->setMaxHealth(10);
                    npc->oCNpc->setVisualWithString("HUMANS.MDS");
                    npc->oCNpc->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);
                    //npc->oCNpc->setTalentValue(0, 10); // Strength
                    //npc->oCNpc->setTalentValue(1, 10); //Dexterity
                    npc->oCNpc->callVariable<int>(OCNpc::Offset::DEXTERITY) = 10;
                    npc->oCNpc->callVariable<int>(OCNpc::Offset::STRENGTH) = 10;
                    npc->oCNpc->enableWithdCoords(pMainPlayer->getX(), pMainPlayer->getZ(), pMainPlayer->getY());
                    npc->setName("Steve");

                } else {
                    //std::cout << "Setting Anims..\n";
                    DataStructures::LastAnimation npcLastAnim = npc->getLastAnimation();
                    DataStructures::LastAnimation npcNewAnim = pMainPlayer->getLastAnimation();
                    std::unique_ptr<zCModel> npcModel = std::make_unique<zCModel>(npc->oCNpc->getModel());


                    for (auto &newId : npcNewAnim.animationIds)
                    {
                        npcModel->startAniInt(newId, 0);
                    }

                    for (auto &lastId : npcLastAnim.animationIds)
                    {
                        bool found = false;
                        for (auto &newId : npcNewAnim.animationIds)
                        {
                            if (lastId == newId)
                            {
                                found = true;
                            }
                        }
                        if (!found)
                        {
                            void *aniActive = npcModel->getActiveAni(lastId);
                            if (aniActive)
                                npcModel->stopAnimationInt(lastId);
                        }
                    }

                    /*if(pMainPlayer->oCNpc->getWeaponMode != nullptr){
                        std::cout << "Weapon is drawn.\n";
                        npc->oCNpc->setWeaponMode(1);
                    }*/
                    std::cout << "WeaponMode: " << std::to_string(pMainPlayer->oCNpc->getWeaponMode()) << "\n";
                    npc->oCNpc->setWeaponMode(pMainPlayer->oCNpc->getWeaponMode());
                    oCMsgWeapon *  c = oCMsgWeapon::CreateoCMsgWeapon(1, 0, 0);
                    npc->oCNpc->EV_DrawWeapon1(c);


                    //zCEventManager* em = OCNpc::GetEM(1);

        // Nachricht ins System schicken
                    //em->onMessage(c, npc->oCNpc);
                }
            }

        }
    private:
        std::unique_ptr<Npc> pMainPlayer;
        Npc *npc;
};