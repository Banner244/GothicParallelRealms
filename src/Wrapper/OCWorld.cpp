#include "OCWorld.h"
#include <cstdint>

void OCWorld::AddVobAsChild(void * vob, void * zCTree){ // STATIC
    using _AddVobAsChild = void(__thiscall *)(void *pThis, void *vob, void *zCTree);
    _AddVobAsChild addVobAsChildRef = (_AddVobAsChild)(0x5f60d0);
    addVobAsChildRef(GetOCWorldAddress(), vob, zCTree);
}

void OCWorld::UpdateVobTreeBspDependencies(void * vob){
    /*using _GetVobHashIndex = unsigned long(__thiscall *)(void *pThis, void *vobParam);
    _GetVobHashIndex getVobHashIndexRef = (_GetVobHashIndex)(0x5f9720);
    return getVobHashIndexRef(GetOCWorldAddress(), vob);*/
}


void OCWorld::PrintStatus()
{ // STATIC
    using _PrintStatus = void(__thiscall *)(void *pThis);
    _PrintStatus printStatusRef = (_PrintStatus)(0x5f6bf0);
    printStatusRef(GetOCWorldAddress());
}

void OCWorld::PrintGlobalVobTree(void * zCTree, int param2) 
{
    using _PrintGlobalVobTree = void(__thiscall *)(void *pThis, void *zCTree, int param2);
    _PrintGlobalVobTree printGlobalVobTreeRef = (_PrintGlobalVobTree)(0x5f74c0);
    printGlobalVobTreeRef(GetOCWorldAddress(), zCTree, param2);
}

void * OCWorld::GetOwnerSession()
{ // STATIC
    using _GetOwnerSession = void * (__thiscall *)(void *pThis);
    _GetOwnerSession getOwnerSessionRef = (_GetOwnerSession)(0x5f9c40);
    return getOwnerSessionRef(GetOCWorldAddress());
}

unsigned long OCWorld::GetVobHashIndex(void *vob)
{
    using _GetVobHashIndex = unsigned long(__thiscall *)(void *pThis, void *vobParam);
    _GetVobHashIndex getVobHashIndexRef = (_GetVobHashIndex)(0x5f9720);
    return getVobHashIndexRef(GetOCWorldAddress(), vob);
}

void OCWorld::InsertVobHashTable(void *vob)
{ // STATIC
    using _InsertVobHashTable = void(__thiscall *)(void *pThis, void *vobParam);
    _InsertVobHashTable insertVobHashTableRef = (_InsertVobHashTable)(0x5f9760);
    insertVobHashTableRef(GetOCWorldAddress(), vob);
}

int OCWorld::ShouldAddThisVobToBsp(void *vob)
{ // STATIC
    using _ShouldAddThisVobToBsp = int(__thiscall *)(void *pThis, void *vobParam);
    _ShouldAddThisVobToBsp shouldAddThisVobToBspRef = (_ShouldAddThisVobToBsp)(0x5f62e0);
    return shouldAddThisVobToBspRef(GetOCWorldAddress(), vob);
}

void OCWorld::EnableVob(void *vob1, void *vob2)
{ // STATIC
    using _EnableVob = void(__thiscall *)(void *pThis, void *vobParam1, void *vobParam2);
    _EnableVob enableVobRef = (_EnableVob)(0x6d7130);
    enableVobRef(GetOCWorldAddress(), vob2, vob1);
}

void OCWorld::InsertInLists(void *vob)
{ // STATIC
    using _InsertInLists = void(__fastcall *)(void *vobParam);
    _InsertInLists insertInListsRef = (_InsertInLists)(0x6d7670);
    insertInListsRef(vob);
}

void OCWorld::VobAddedToWorld(void *vob) // Keeps the VOB in the world but as Object
{ // STATIC
    using _VobAddedToWorld = void(__thiscall *)(void *pThis, void *vobParam);
    _VobAddedToWorld addVobRef = (_VobAddedToWorld)(0x5f6360);
    addVobRef(GetOCWorldAddress(), vob);
}

void *OCWorld::AddVob(void *vob)
{ // STATIC
    using _AddVob = void * (__thiscall *)(void *pThis, void *vobParam);
    _AddVob addVobRef = (_AddVob)(0x5f6340);
    return addVobRef(GetOCWorldAddress(), vob);
}

void OCWorld::RemoveVob(void *vob)
{ // STATIC
    using _RemoveVob = void(__thiscall *)(void *pThis, void *vobParam);
    _RemoveVob removeVobRef = (_RemoveVob)(0x5f66c0);
    removeVobRef(GetOCWorldAddress(), vob);
}

void *OCWorld::GetOCWorldGlobalVobTree()
{                                                               // STATIC     // glVobTree ofs
    return *(void **)(((uintptr_t)GetOCWorldAddress()) + 0x24); // Continue here, somehow getting 0000000
}

void *OCWorld::GetOCWorldAddress()
{ // STATIC
    /*using _GetGameWorld = void * (__thiscall *)(void *pThis);
    _GetGameWorld getGameWorldRef = (_GetGameWorld)(0x638a90);
    return getGameWorldRef(OCGame::getOCGameAddress());*/
    //return *(void **)0x86D3DC; // 8DC238, 8DC670, 86A3E0
    return *(void **)(((uintptr_t) 0x86A3E0));
}

/*void * OCWorld::GetOCWorldGlobalVobTree()
{ // STATIC     // Word ofs, glVobTree ofs
    void * pointing = GetOCWorldAddress();
    void * sec = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pointing) + 0x24);
    return sec; // Continue here, somehow getting 0000000
}

void * OCWorld::GetOCWorldAddress()
{ // STATIC
    //return *(void **)(((uintptr_t)OCGame::getOCGameAddress()) + 0x8c);
    using _GetGameWorld = void * (__thiscall *)(void *pThis);
    _GetGameWorld getGameWorldRef = (_GetGameWorld)(0x638a90);

    return *(void **)(((uintptr_t)getGameWorldRef(OCGame::getOCGameAddress())));
}*/

/* VTable Way
    // VMT-Zeiger aus gameInstance holen
    void **vtable = *(void ***)OCGame::getOCGameAddress();

    // Funktion bei Offset 0x34 aus der VMT holen
    using GetWorldFunc = void *(__thiscall *)(void *);
    GetWorldFunc getWorld = (GetWorldFunc)vtable[0x34 / 4];

    std::cout << "MyWay: " << getGameWorldRef(OCGame::getOCGameAddress()) << ", not MY: " << getWorld(OCGame::getOCGameAddress()) << std::endl;
    // Funktion aufrufen und zCWorld-Adresse zurückgeben
    return getWorld(OCGame::getOCGameAddress());

*/