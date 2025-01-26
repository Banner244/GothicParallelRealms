#include "MessageGameThreadManager.h"

MessageGameThreadManager::MessageGameThreadManager(){
    clients = new std::unordered_map<std::string, Npc*>();
    messageHandler = new MessageHandler(clients);
}

void MessageGameThreadManager::addTask(std::string task)
{
    gameThreadTasks.push_back(task);
}

void MessageGameThreadManager::removeTask(std::vector<std::string>::iterator it)
{
    //gameThreadTasks.erase(it);
    if(!gameThreadTasks.empty())
        gameThreadTasks.erase(it);
        //gameThreadTasks.erase(gameThreadTasks.begin() + 0);
}

void MessageGameThreadManager::processMessages()
{
    std::vector<std::string>::iterator firstTask = gameThreadTasks.begin();

    if (firstTask == gameThreadTasks.end()) {
        return;
    }

    messageHandler->managePacket(*firstTask);
    removeTask(firstTask);
}