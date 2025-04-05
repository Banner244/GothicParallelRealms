#pragma once

#include <iostream>
#include "zSTRING.h"

class zCModel {
    public:
        using _StartAnimation = void(__thiscall *)(void *pThis, zSTRING * animName);
        using _IsAnimationActive = int(__thiscall *)(void *pThis, zSTRING * animName);
        using _StopAnimation = void(__thiscall *)(void *pThis, zSTRING * animName);
        using _StopAnimationInt = void(__thiscall *)(void *pThis, int id);

        using _StartAni = void(__thiscall *)(void *pThis, void * zcModelAni, int frame);
        using _StartAniInt = void(__thiscall *)(void *pThis, int id, int frame);
        using _GetAniFromAniID = void*(__thiscall *)(void *pThis, int frame);
        using _SearchAniIndex = int(__thiscall *)(zSTRING * animName);// Static Function
        using _GetActiveAni = void*(__thiscall *)(void *pThis, int id);
        using _ShowAniList = void(__thiscall *)(void *pThis, int param);

        _StartAnimation startAnimationRef;
        _IsAnimationActive isAnimationActiveRef;
        _StopAnimation stopAnimationRef;
        _StopAnimationInt stopAnimationIntRef;

        _StartAni startAniRef;
        _StartAniInt startAniIntRef;
        _GetAniFromAniID getAniFromAniIDRef;
        _SearchAniIndex searchAniINdexRef;
        _GetActiveAni getActiveAniRef;
        _ShowAniList showAniListRef;


        zCModel(void *pThis);

        void *getAddress() const;

        void startAnimation(char * animName);
        int isAnimationActive(char * animName);
        void stopAnimation(char * animName);
        void stopAnimationInt(int id);
        void startAni(void * zcModelAni, int frame);
        void startAniInt(int id, int frame);

        void * getAniFromAniID(int id);

        int SearchAniIndex(char * aniName);

        void * getActiveAni(int id);

        void showAniList(int param);

    private:
        void initializeFunctionPointers();
        void * pThis;
        
};