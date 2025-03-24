#include "OCGame.h"

void * OCGame::GetSpawnManager() {
    using _GetSpawnManager = void * (__thiscall *)(void *pThis);
    _GetSpawnManager getSpawnManagerRef = (_GetSpawnManager)(0x638b50);
    return getSpawnManagerRef(getOCGameAddress());
}

void OCGame::InsertPlayerIntoWorld(void * vob, void * zMAT4Param) { // STATIC
    using _InsertPlayerIntoWorld = void(__thiscall *)(void *pThis, void *vobParam1, void *vobParam2);
    _InsertPlayerIntoWorld insertPlayerIntoWorldRef = (_InsertPlayerIntoWorld)(0x63aba0);
    insertPlayerIntoWorldRef(getOCGameAddress(), vob, zMAT4Param);
}


void * OCGame::getOCGameAddress(){// STATIC
    return *(void **)0x8DA6BC;
}