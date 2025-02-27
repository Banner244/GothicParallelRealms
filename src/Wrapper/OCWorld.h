#pragma once

#include "OCGame.h"

class OCWorld {

    public:
    //using _OCNpcCtor = void *(__thiscall *)(void *pThis);
        static void addVob(void * vob);
        static void * getOCWorldAddress();
    private:
        /*using _AddVob = void * (__thiscall )(void *pThis, void *vob);
        _AddVob addVobRef;*/
    /*typedef void(__thiscall *_AddVob)(void *pThis, void *vobParam);
    _AddVob addVob;
    typedef unsigned long(__thiscall *_GetVobHashIndex)(void *pThis, void *vobParam);
    _GetVobHashIndex getVobHashIndex;
    typedef void(__thiscall *_PrintStatus)(void *pThis);
    _PrintStatus printStatus;*/

        //void *pThis = *(void **)(((uintptr_t)oCGame.pThis) + 0x8c); // WORKS TOO

};