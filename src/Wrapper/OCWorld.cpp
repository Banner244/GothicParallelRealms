#include "OCWorld.h"
#include <cstdint>

void OCWorld::addVob(void * vob) { // STATIC
    typedef void(__thiscall *_AddVob)(void *pThis, void *vobParam);
    _AddVob addVobRef = (_AddVob)(0x5f6340);
    addVobRef(getOCWorldAddress(), vob);
}

void * OCWorld::getOCWorldAddress() { // STATIC
    return *(void **)(((uintptr_t)OCGame::getOCGameAddress()) + 0x8c);
}