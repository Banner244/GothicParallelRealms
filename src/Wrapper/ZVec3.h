#pragma once

#include <iostream>
#include <string>

// In GOTHIC: X; Z; Y
class ZVec3
{
private:
    float posX;
    float posZ;
    float posY;



public:
    ZVec3();
    ZVec3(float x, float z, float y);

    void initialize(float posX, float posZ, float posY);

    std::string getPos();

    float getPosX();
    float getPosZ();
    float getPosY();
    /*      float getPosY();
          void setPosY(float posY);*/

    // Operators overloaded
    ZVec3 operator+(const ZVec3 &other) const
    {
        return ZVec3(posX + other.posX, posZ + other.posZ, posY + other.posY);
    }

    ZVec3 operator-(const ZVec3 &other) const
    {
        return ZVec3(posX - other.posX, posZ - other.posZ, posY - other.posY);
    }

    ZVec3 operator*(float factor) const
    {
        return ZVec3(posX * factor, posZ * factor, posY * factor);
    }
};