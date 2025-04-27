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

/**
 * @class GameThreadWorker
 * @brief Manages game-related tasks and message processing in the thread of the Game itself.
 *
 * The GameThreadWorker class is responsible for handling asynchronous game tasks,
 * processing incoming messages, and managing client-related operations.
 * It utilizes a task queue to schedule and execute various game-related functions
 * efficiently.
 *
 * @details
 * - Maintains a list of active NPC clients.
 * - Processes messages from the network.
 * - Manages game state checks and scheduled tasks.
 * - Interfaces with a MessageHandler for handling communication.
 *
 * @note This class should be used in a multi-threaded environment to offload 
 *       game-related computations from the main game loop.
 */
class GameThreadWorker {

    public:
        GameThreadWorker();
        /**
         * @brief Pointer to a map containing active NPC clients, indexed by their IP/Port combination.
        */
        std::unordered_map<std::string, Npc*> *clients;


        ~GameThreadWorker();

        
        /**
         * @brief Processes incoming network messages.
         * 
         * This method should be called periodically to handle messages 
         * received from server and update the game state accordingly.
         */
        void processMessages();

        /**
         * @brief Checks and updates the current game state.
         * 
         * This method ensures that the game remains in a consistent and valid state.
         */
        void checkGameState();


        /**
        * @brief Adds a new task to the game thread's task queue.
        * 
        * @param task The Buffer of the received Message from Server
        */
        void addTask(std::string task);

        /**
        * @brief Removes the next task from the task queue.
        * 
        * This method is called when a task has been completed.
        */
        void removeTask();

        /**
        * @brief Associates a specific client with the message handler.
        * 
        * @param client Reference to the client instance.
        */
        void setClientForHandler(Client &client);
    private:
        /**
         * @brief Queue of tasks to be processed by the game thread.
         */
        std::queue<std::string> gameThreadTasks;
        /**
        * @brief Pointer to the MessageHandler responsible for processing communication.
        */
        MessageHandler * messageHandler;

        Npc *pMainPlayer;
};