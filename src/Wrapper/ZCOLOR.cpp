#include "ZCOLOR.h"

// Constructor
typedef void(__thiscall *_zCOLORCtor)(void *pThis, int param_1);
_zCOLORCtor zCOLORCTor;

typedef void(__thiscall *_zCOLORCtor2)(void *pThis, unsigned char param1, unsigned char param2, unsigned char param3, unsigned char param4);
_zCOLORCtor2 zCOLORCTor2;

void ZCOLOR::initialize(int param_1)
{
    // calling constructor
    zCOLORCTor = (_zCOLORCtor)(0x401de0);
    zCOLORCTor(this, param_1);
}

void ZCOLOR::initialize()
{
    // calling constructor2
    zCOLORCTor2 = (_zCOLORCtor2)(0x6e1bc0);
    zCOLORCTor2(this, 0xff, 0xd7, '\0', 0xff);
}

// Methode zum Ausgeben der Farbwerte
std::string ZCOLOR::getColor()
{
    return "Color: " + std::to_string(color[0]) + ", " +
           std::to_string(color[1]) + ", " +
           std::to_string(color[2]) + ", " +
           std::to_string(color[3]) + ", " +
           std::to_string(color[4]);
}
