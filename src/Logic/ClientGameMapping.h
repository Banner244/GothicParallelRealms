#pragma once

#include <iostream>
#include <string>

#include "../Models/DataStructures.h"
#include "../Models/Npc.h"

#include "../../common/src/Async/AsyncUnorderedMap.h"

class ClientGameMapping {

    public:
        ClientGameMapping(AsyncUnorderedMap<std::string, Npc*> *pClients);

        void manageClientsInSync();
    private:
        AsyncUnorderedMap<std::string, Npc*> *pClients;

        void syncAnimation();
};

