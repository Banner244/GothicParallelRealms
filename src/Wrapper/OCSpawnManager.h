#pragma once

#include <iostream>
#include <string> 
#include "ZVec3.h"

class OCSpawnManager {
    private:


    public:
        // Wrapper für den ursprünglichen Konstruktor
        void initialize();

        void initializeExisting(uintptr_t originAddress);
        //std::string getValues();

        void spawnImmediately(int param1);
        void spawnNpcVec(void *npc, ZVec3 * coords, float param3);

};