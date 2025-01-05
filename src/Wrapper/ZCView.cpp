#include "ZCView.h"


typedef void(__thiscall *_zCViewCtor)(void *pThis);
_zCViewCtor zCViewCtor;

void ZCView::initialize()
{
    zCViewCtor = (_zCViewCtor)(0x6fbb60);
    zCViewCtor(this);
}

std::string ZCView::getValues()
{
    return std::to_string(field_30) + " " + std::to_string(field_34) + " " + std::to_string(field_2c) + " " + std::to_string(field_84) + " " + std::to_string(field_80) + " " + field_cc;
}