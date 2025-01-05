#include "zSTRING.h"

typedef void(__thiscall *_zSTRINGCtor)(void *pThis, char *str);
_zSTRINGCtor zSTRINGCTor;

zSTRING::zSTRING() : data(nullptr), length(0), capacity(0) {
    
}

// Wrapper für den ursprünglichen Konstruktor
void zSTRING::initialize(char *str)
{
    zSTRINGCTor = (_zSTRINGCtor)(0x4013a0);
    zSTRINGCTor(this, str);
}

std::string zSTRING::getStr()
{
    return std::string(data ? data : "-") + " " + std::to_string(length) + " " + std::to_string(capacity);
}

void zSTRING::setString(char *str)
{
    this->data = str;
}