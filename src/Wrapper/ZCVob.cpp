#include "ZCVob.h"




typedef void(__thiscall *_zCVobCtor)(void *pThis);
_zCVobCtor zCVobCtor;

typedef void(__thiscall *_SetPositionWorld)(void *pThis, ZVec3 * param1);
_SetPositionWorld tSetPositionWorld;


void ZCVob::initialize()
{
    zCVobCtor = (_zCVobCtor)(0x5d3030);
    zCVobCtor(this);
}

void ZCVob::setPostitionWorld(ZVec3 * coords){
    tSetPositionWorld = (_SetPositionWorld)(0x5ee650);
    tSetPositionWorld(this, coords);
}

std::string ZCVob::getValues()
{
    return "";
}