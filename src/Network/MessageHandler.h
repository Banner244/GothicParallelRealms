#pragma once

#include <iostream>
#include <unordered_map>

#include "../Models/Npc.h"
#include "../Wrapper/zCModel.h"
#include "../../server/src/PacketIDs.h"
#include "../../server/src/Data.h"
#include <mutex>

class MessageHandler {
    public:
        MessageHandler(std::unordered_map<std::string, Npc*> *clients);
        
        void managePacket(std::string stringPacket);
    private:
        std::unordered_map<std::string, Npc*> *clients;
        std::mutex clientsMutex;
        void handleServerHandshakeAccept(Data data);
        void handleServerDistributePosition(Data data);
        void handleServerDistributeAnimations(Data data);
        void handleServerDistributeRotations(Data data);
};