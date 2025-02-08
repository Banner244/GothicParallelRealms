#pragma once

#include <iostream>
#include <vector>

#include "../Models/DataStructures.h"
#include "Client.h"

#include <functional>

class DataChangeNotifier {

    public:
        DataChangeNotifier(Client *client);

        void sendChanges();

    private:
        void initListValues();

        std::vector<std::function<void()>> playerState;

        Client * pClient;
        Npc * pMainPlayer;

        DataStructures::LastPosition playerLastPos;
        DataStructures::LastAnimation playerLastAnim;
        DataStructures::LastRotation playerLastRotation;
};