#pragma once

#include <iostream>
#include <unordered_map>

#include "../Models/Npc.h"
#include "../Wrapper/zCModel.h"
#include "../../server/src/Packets.h"
#include "../../server/src/PackagingSystem.h"
#include <mutex>

class MessageHandler {
    public:
        MessageHandler(std::unordered_map<std::string, Npc*> *clients);
        
        void managePacket(std::string stringPacket);
    private:
        std::unordered_map<std::string, Npc*> *clients;
        std::mutex clientsMutex;
        void handleServerHandshakeAccept(std::string &buffer);
        void handleServerDistributePosition(std::string &buffer);
        void handleServerDistributeAnimations(std::string &buffer);
        void handleServerDistributeRotations(std::string &buffer);
};