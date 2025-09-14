#pragma once

#include "OCNpc.h"
#include "zCEventMessage.h"

class OCNpc;
class zCEventManager {

public:
    void onMessage(zCEventMessage* event, OCNpc * npc);
};