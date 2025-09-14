#pragma once

#include "zCEventMessage.h"

class oCMsgWeapon : public zCEventMessage {
    public:
        static oCMsgWeapon * CreateoCMsgWeapon(int tWeaponSubType, int param2, int param3);


};

