#pragma once

#include <iostream>
#include <unordered_map>
#include <mutex>

#include "../Network/Client.h"
#include "../Models/Npc.h"
#include "../Wrapper/zCModel.h"
#include "../../server/src/Packets.h"
#include "../../server/src/PackagingSystem.h"

class Client;

class MessageHandler {
    public:
        MessageHandler(std::unordered_map<std::string, Npc*> *clients);
        
        void managePacket(std::string stringPacket);

        void setClient(Client &client);
    private:
        std::unordered_map<std::string, Npc*> *clients;
        Client * pClient;
        std::mutex clientsMutex;
        void handleServerHandshakeAccept(std::string &buffer);
        void handleServerRequestsHeartbeat(std::string &buffer);
        void handleServerDistributePosition(std::string &buffer);
        void handleServerDistributeAnimations(std::string &buffer);
        void handleServerDistributeRotations(std::string &buffer);
};