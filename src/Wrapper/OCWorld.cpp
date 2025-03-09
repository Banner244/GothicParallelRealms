#include "OCWorld.h"
#include <cstdint>

int OCWorld::ShouldAddThisVobToBsp(void * vob) { // STATIC
    using _ShouldAddThisVobToBsp = int(__thiscall *)(void *pThis, void *vobParam);
    _ShouldAddThisVobToBsp shouldAddThisVobToBspRef = (_ShouldAddThisVobToBsp)(0x5f62e0);
    return shouldAddThisVobToBspRef(GetOCWorldAddress(), vob);
}

void OCWorld::EnableVob(void * vob1, void * vob2) { // STATIC
    using _EnableVob = void(__thiscall *)(void *pThis, void *vobParam1, void *vobParam2);
    _EnableVob enableVobRef = (_EnableVob)(0x6d7130);
    enableVobRef(GetOCWorldAddress(), vob2, vob1);
}

void OCWorld::InsertInLists(void * vob) { // STATIC
    using _InsertInLists = void(__fastcall *)(void *vobParam);
    _InsertInLists insertInListsRef = (_InsertInLists)(0x6d7670);
    insertInListsRef(vob);
}

void OCWorld::VobAddedToWorld(void * vob) { // STATIC
    using _VobAddedToWorld = void(__thiscall *)(void *pThis, void *vobParam);
    _VobAddedToWorld addVobRef = (_VobAddedToWorld)(0x5f6360);
    addVobRef(GetOCWorldAddress(), vob);
}

void OCWorld::AddVob(void * vob) { // STATIC
    typedef void(__thiscall *_AddVob)(void *pThis, void *vobParam);
    _AddVob addVobRef = (_AddVob)(0x5f6340);
    addVobRef(GetOCWorldAddress(), vob);
}

void OCWorld::RemoveVob(void * vob) { // STATIC
    using _RemoveVob = void(__thiscall *)(void *pThis, void *vobParam);
    _RemoveVob addVobRef = (_RemoveVob)(0x5f66c0);
    addVobRef(GetOCWorldAddress(), vob);
}

void * OCWorld::GetOCWorldAddress() { // STATIC
    return *(void **)(((uintptr_t)OCGame::getOCGameAddress()) + 0x8c);
}