#include "ZVec3.h"

typedef void(__thiscall *_ClassCtor)(void *pThis, float posX, float posZ, float posY);
_ClassCtor ZVec3CTor;

void ZVec3::initialize(float posX, float posZ, float posY)
{
    ZVec3CTor = (_ClassCtor)(0x408c20);
    ZVec3CTor(this, posX, posZ, posY);
}

std::string ZVec3::getPos()
{
    return std::to_string(this->posX) + " " + std::to_string(posZ) + " " + std::to_string(posY);
}

/*float ZVec3::getPosY()
{
    return this->posY;
}

void ZVec3::setPosY(float posY) {
    this->posY = posY;
}*/