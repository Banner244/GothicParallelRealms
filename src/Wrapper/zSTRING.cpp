#include "zSTRING.h"

zSTRING* zSTRING::CreateNewzSTRING(char * str){ // STATIC
    void* raw = ::operator new(sizeof(zSTRING));

    using _CTor = zSTRING*(__thiscall *)(void *pThis, char * text);
    _CTor ctor = reinterpret_cast<_CTor>(0x004013A0);
     ctor(raw, str);

    //return u;
    return reinterpret_cast<zSTRING*>(raw);
}

void zSTRING::Assign(zSTRING* str, char* text) // STATIC
{
    using _zSTRINGAssign = zSTRING* (__thiscall*)(zSTRING* thisPtr, char *param_1);
    _zSTRINGAssign assign = reinterpret_cast<_zSTRINGAssign>(0x004c5820);

    assign(str, text);
}