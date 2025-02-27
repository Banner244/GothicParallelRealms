#include "OCWorld.h"
#include <cstdint>

void OCWorld::insertInLists(void * vob) { // STATIC
    using _InsertInLists = void(__fastcall *)(void *vobParam);
    _InsertInLists insertInListsRef = (_InsertInLists)(0x6d7670);
    insertInListsRef(vob);
}

void OCWorld::vobAddedToWorld(void * vob) { // STATIC
    using _VobAddedToWorld = void(__thiscall *)(void *pThis, void *vobParam);
    _VobAddedToWorld addVobRef = (_VobAddedToWorld)(0x5f6360);
    addVobRef(getOCWorldAddress(), vob);
}

void OCWorld::addVob(void * vob) { // STATIC
    typedef void(__thiscall *_AddVob)(void *pThis, void *vobParam);
    _AddVob addVobRef = (_AddVob)(0x5f6340);
    addVobRef(getOCWorldAddress(), vob);
}

void OCWorld::removeVob(void * vob) { // STATIC
    using _RemoveVob = void(__thiscall *)(void *pThis, void *vobParam);
    _RemoveVob addVobRef = (_RemoveVob)(0x5f66c0);
    addVobRef(getOCWorldAddress(), vob);
}

void * OCWorld::getOCWorldAddress() { // STATIC
    return *(void **)(((uintptr_t)OCGame::getOCGameAddress()) + 0x8c);
}