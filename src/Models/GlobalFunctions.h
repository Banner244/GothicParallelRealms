#pragma once

#include "../Wrapper/zSTRING.h"
#include "../Wrapper/OCNpc.h"

struct GlobalFunctions {
    typedef void(__stdcall * _FuncA)();
    _FuncA funca;

    typedef void(__fastcall * _Print)(zSTRING * string ); 
    _Print print;

    typedef void(__cdecl * _StdPrintwin)(zSTRING * param1);
    _StdPrintwin stdPrintWin;

    typedef void(__cdecl * _CheatConsole)();
    _CheatConsole openCheatConsole = (GlobalFunctions::_CheatConsole)(0x647129);

    typedef void(__cdecl * _PrintDebug)(char * str, int param2 ); 
    _PrintDebug printDebug;

    typedef void(__cdecl * _GlobAddRefVobSubtree)(OCNpc * npc);
    _GlobAddRefVobSubtree addRefVobSubtree = reinterpret_cast<_GlobAddRefVobSubtree>(0x6a4490);;

};

extern GlobalFunctions globalFunction;