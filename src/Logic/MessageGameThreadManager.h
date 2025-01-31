#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include "../Network/Client.h"

#include "../Wrapper/OCNpc.h"
#include "../Wrapper/zCModel.h"
#include "../Network/MessageHandler.h"

class MessageGameThreadManager {

    public:
        MessageGameThreadManager();
        std::unordered_map<std::string, Npc*> *clients;

        void processMessages();

        void addTask(std::string task);
        void removeTask(std::vector<std::string>::iterator it);


    private:
        std::vector<std::string> gameThreadTasks;
        MessageHandler * messageHandler;

};