#include "ZVec3.h"

typedef void(__thiscall *_ClassCtor)(void *pThis, float posX, float posZ, float posY);
_ClassCtor ZVec3CTor;

ZVec3::ZVec3() {}

ZVec3::ZVec3(float x, float z, float y) : posX(x), posZ(z), posY(y)
{
    initialize(x, z, y);
}

void ZVec3::initialize(float posX, float posZ, float posY)
{
    ZVec3CTor = (_ClassCtor)(0x408c20);
    ZVec3CTor(this, posX, posZ, posY);
    std::cout << "Initialized ZVec at: " << getPos() << std::endl;
}

std::string ZVec3::getPos()
{
    return std::to_string(this->posX) + " " + std::to_string(posZ) + " " + std::to_string(posY);
}

float ZVec3::getPosX()
{
    return this->posX;
}

float ZVec3::getPosZ()
{
    return this->posZ;
}

float ZVec3::getPosY()
{
    return this->posY;
}

/*float ZVec3::getPosY()
{
    return this->posY;
}

void ZVec3::setPosY(float posY) {
    this->posY = posY;
}*/