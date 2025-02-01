#pragma once

#include <iostream>
#include "zSTRING.h"

class zCModel {
    public:
        using _StartAnimation = void(__thiscall *)(void *pThis, zSTRING * animName);
        using _IsAnimationActive = int(__thiscall *)(void *pThis, zSTRING * animName);
        using _StopAnimation = void(__thiscall *)(void *pThis, zSTRING * animName);

        _StartAnimation startAnimationRef;
        _IsAnimationActive isAnimationActiveRef;
        _StopAnimation stopAnimationRef;

        zCModel(void *pThis);

        void *getAddress() const;

        void startAnimation(char * animName);
        int isAnimationActive(char * animName);
        void stopAnimation(char * animName);
    private:
        void initializeFunctionPointers();
        void * pThis;
        
};