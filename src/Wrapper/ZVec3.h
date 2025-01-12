#pragma once

#include <iostream>
#include <string> 

// In GOTHIC: X; Z; Y
class ZVec3 {
    private:
        float posX;
        float posZ;
        float posY;

    public:

        void initialize(float posX, float posZ, float posY);

        std::string getPos();

        float getPosX();
        float getPosZ();
        float getPosY();
  /*      float getPosY();
        void setPosY(float posY);*/
};