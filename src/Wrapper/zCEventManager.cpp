#include "zCEventManager.h"

void zCEventManager::onMessage(zCEventMessage* event, OCNpc * npc){
    using _OnMessage = void(__thiscall *)(void *pThis, zCEventMessage* event, OCNpc * npc);
    _OnMessage onMessageRef = reinterpret_cast<_OnMessage>(0x6dd090);
    onMessageRef(this, event, npc);
}