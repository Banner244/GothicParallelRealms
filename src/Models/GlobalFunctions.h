#pragma once

#include "../Wrapper/zSTRING.h"

struct GlobalFunctions {
    typedef void(__stdcall * _FuncA)();
    _FuncA funca;

    typedef void(__fastcall * _Print)(zSTRING * string ); 
    _Print print;

    typedef void(__cdecl * _StdPrintwin)(zSTRING * param1);
    _StdPrintwin stdPrintWin;

    typedef void(__cdecl * _CheatConsole)();
    _CheatConsole openCheatConsole;

    typedef void(__cdecl * _PrintDebug)(char * str, int param2 ); 
    _PrintDebug printDebug;

};

extern GlobalFunctions globalFunction;