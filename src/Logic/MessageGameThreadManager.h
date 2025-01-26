#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include "../Network/Client.h"

#include "../Wrapper/OCNpc.h"

#include "../Network/MessageHandler.h"

class MessageGameThreadManager {

    public:
        MessageGameThreadManager();
        std::unordered_map<std::string, Npc*> *clients;

        void processMessages();

        void addTask(std::string task);


    private:
        std::vector<std::string> gameThreadTasks;
        MessageHandler * messageHandler;

};