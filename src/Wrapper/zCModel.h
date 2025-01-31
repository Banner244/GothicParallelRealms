#pragma once

#include <iostream>
#include "zSTRING.h"

class zCModel {
    public:
        using _StartAnimation = void(__thiscall *)(void *pThis, zSTRING * animName);
        _StartAnimation startAnimationRef;

        zCModel(void *pThis);

        void startAnimation(char * animName);
        void * pThis;
    private:
        void initializeFunctionPointers();
        
};