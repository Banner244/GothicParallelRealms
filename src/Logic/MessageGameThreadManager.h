#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include "../Models/GlobalFunctions.h"

#include "../Wrapper/OCNpc.h"
#include "../Wrapper/zCModel.h"
#include "../Wrapper/OCWorld.h"

#include "../Network/Client.h"
#include "../Network/MessageHandler.h"

class Client;
class Npc;
class MessageHandler;

class MessageGameThreadManager {

    public:
        MessageGameThreadManager();
        std::unordered_map<std::string, Npc*> *clients;
        //std::mutex clientsMutex;
        void processMessages();

        void addTask(std::string task);
        void removeTask(std::vector<std::string>::iterator it);

        void setClientForHandler(Client &client);
    private:
        std::vector<std::string> gameThreadTasks;
        MessageHandler * messageHandler;

};