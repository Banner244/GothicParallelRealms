#pragma once

#include <iostream>
#include <string> 

#include "ZVec3.h"

class ZCVob {
    private:
        /*int iVar1;
        bool bVar2;*/
    public:
        // Wrapper für den ursprünglichen Konstruktor
        void initialize();

        std::string getValues();

        void setPostitionWorld(ZVec3 * coords);
};