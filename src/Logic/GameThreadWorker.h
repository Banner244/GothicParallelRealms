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

class Client;
class Npc;
class MessageHandler;

class GameThreadWorker {

    public:
        GameThreadWorker();
        std::unordered_map<std::string, Npc*> *clients;
        //std::mutex clientsMutex;
        void processMessages();
        void checkGameState();

        void addTask(std::string task);
        void removeTask();

        void setClientForHandler(Client &client);
    private:
        std::queue<std::string> gameThreadTasks;
        MessageHandler * messageHandler;

};