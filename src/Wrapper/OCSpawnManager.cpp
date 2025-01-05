#include "OCSpawnManager.h"

typedef void(__thiscall * _SpawnImmediately)(void* pThis, int param1);
_SpawnImmediately tSpawnImmediately;

typedef void(__thiscall * _SpawnNpcVec)(void* pThis, void *npc, ZVec3 * coords, float param3);
_SpawnNpcVec tSpawnNpcVec;

typedef void(__thiscall *_OCSpawnManagerCtor)(void *pThis);
_OCSpawnManagerCtor oCSpawnManagerCtor;

void OCSpawnManager::initialize()
{
    oCSpawnManagerCtor = (_OCSpawnManagerCtor)(0x6cf4d0);
    oCSpawnManagerCtor(this);
}

void OCSpawnManager::initializeExisting(uintptr_t originAddress) {
// uintptr_t
}

/*std::string OCSpawnManager::getValues()
{
    return std::to_string(field_30) + " " + std::to_string(field_34) + " " + std::to_string(field_2c) + " " + std::to_string(field_84) + " " + std::to_string(field_80) + " " + field_cc;
}*/

void OCSpawnManager::spawnImmediately(int param1) {
    tSpawnImmediately = (_SpawnImmediately)(0x6cf800);
    tSpawnImmediately(this, param1);
}

void OCSpawnManager::spawnNpcVec(void *npc, ZVec3 * coords, float param3){
    tSpawnNpcVec = (_SpawnNpcVec)(0x6d0710);
    tSpawnNpcVec(this, npc, coords, param3);
}