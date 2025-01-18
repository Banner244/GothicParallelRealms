#include "sMain.h"
#include <vector>
sMain::sMain()
{
    InitTrainer();
}

void sMain::InitTrainer()
{
}

struct OCGameRef
{
    typedef void(__thiscall *_Func)(void *pThis);
    _Func pause;
    _Func unPause;
    _Func init;

    typedef void(__thiscall *_FuncOneParam)(void *pThis, bool param);
    _FuncOneParam openSaveScreen;

    typedef int(__thiscall *_RetFunc)(void *pThis);
    _RetFunc getShowPlayerStatus;
    _RetFunc getDrawWaynet;

    typedef int(__thiscall *_RetFunc2)(void *pThis, int enumNumber);
    _RetFunc2 openView;

    typedef void *(__thiscall *_GetSpawnManager)(void *pThis);
    _GetSpawnManager getSpawnManager;

    typedef void *(__thiscall *_EnterWorld)(void *pThis, void *npc, int param_2, zSTRING *str);
    _EnterWorld enterWorld;

    void *pThis = *(void **)0x8DA6BC; // Adresse von oCGame
} oCGame;

struct OCWorldRef
{

    typedef void(__thiscall *_AddVob)(void *pThis, void *vobParam);
    _AddVob addVob;

    typedef unsigned long(__thiscall *_GetVobHashIndex)(void *pThis, void *vobParam);
    _GetVobHashIndex getVobHashIndex;

    typedef void(__thiscall *_PrintStatus)(void *pThis);
    _PrintStatus printStatus;

    void *pThis = *(void **)(((uintptr_t)oCGame.pThis) + 0x8c); // WORKS TOO
} oCWorldRef;

struct OCSpawnManagerRef
{
    typedef void *(__thiscall *_SummonNpc)(void *pThis, int param1, ZVec3 *coords, float param3);
    _SummonNpc summonNpc;

    typedef void(__thiscall *_SpawnImmediately)(void *pThis, int param1);
    _SpawnImmediately spawnImmediately;
    typedef void(__thiscall *_SpawnNpcVec)(void *pThis, void *npc, ZVec3 *coords, float param3);
    _SpawnNpcVec spawnNpcVec;
    typedef void(__thiscall *_SpawnNpcString)(void *pThis, void *npc, zSTRING *coords, float param3);
    _SpawnNpcString spawnNpcString;

    // Getting the base address of oCGame and adding offset to turn it into oCSpawnManager
    void *pThis = *(void **)(((uintptr_t)oCGame.pThis) + 0x134);
} oCSpawnManager;

struct ZCViewRef
{
    typedef void(__thiscall *_PrintMessage)(void *pThis, zSTRING *param_1, zSTRING *param_2, float param_3, ZCOLOR *param_4);
    _PrintMessage printMessage;

    typedef void(__thiscall *_PrintTimed)(void *pThis, int param_1, int param_2, zSTRING *param_3, float param_4, ZCOLOR *param_5);
    _PrintTimed printTimed;

    typedef void(__thiscall *_Printwin)(void *pThis, zSTRING *str);
    _Printwin printwin;

    typedef void(__thiscall *_Open)(void *pThis);
    _Open open;

    void *pThis = *(void **)0x8de1bc; // Adresse von CView
} zCViewRef;

void initAddresses()
{
    oCWorldRef.addVob = (OCWorldRef::_AddVob)(0x5f6340);
    oCWorldRef.getVobHashIndex = (OCWorldRef::_GetVobHashIndex)(0x5f9720);
    oCWorldRef.printStatus = (OCWorldRef::_PrintStatus)(0x5f6bf0);

    oCSpawnManager.spawnNpcVec = (OCSpawnManagerRef::_SpawnNpcVec)((0x6d0710));
    oCSpawnManager.spawnImmediately = (OCSpawnManagerRef::_SpawnImmediately)((0x6cf800));
    oCSpawnManager.spawnNpcString = (OCSpawnManagerRef::_SpawnNpcString)((0x6d04c0));
    oCSpawnManager.summonNpc = (OCSpawnManagerRef::_SummonNpc)((0x6d0350));

    zCViewRef.open = (ZCViewRef::_Open)(0x006fd070); // does something...
    zCViewRef.printwin = (ZCViewRef::_Printwin)((0x700d20));
    zCViewRef.printTimed = (ZCViewRef::_PrintTimed)((0x6fe1a0));
    zCViewRef.printMessage = (ZCViewRef::_PrintMessage)(0x6fe5c0);

    oCGame.pause = (OCGameRef::_Func)(0x7dcc48);
    oCGame.unPause = (OCGameRef::_Func)((*(DWORD *)0x7dcc4c));
    oCGame.openSaveScreen = (OCGameRef::_FuncOneParam)((*(DWORD *)0x7dcc88));
    oCGame.getDrawWaynet = (OCGameRef::_RetFunc)((*(DWORD *)0x7dcc54));
    oCGame.init = (OCGameRef::_Func)((*(DWORD *)0x7dcbf4));
    oCGame.openView = (OCGameRef::_RetFunc2)(0x425d4d);
    oCGame.enterWorld = (OCGameRef::_EnterWorld)(0x63ead0);

    globalFunction.printDebug = (GlobalFunctions::_PrintDebug)(0x645280);
    globalFunction.stdPrintWin = (GlobalFunctions::_StdPrintwin)(0x6fc420);
    globalFunction.print = (GlobalFunctions::_Print)(0x756e00);
    globalFunction.openCheatConsole = (GlobalFunctions::_CheatConsole)(0x647129);
}

void sMain::setPositions()
{
    for (const auto& pair : *clients) {
        std::string* key = pair.first; // Zeiger auf den Schlüssel
        Npc* value = pair.second;     // Zeiger auf den Wert

        // Verarbeitung der Schlüssel-Wert-Paare
        std::cout << "Key: " << *key << ", Value: " << value << std::endl;
    }

}

void sMain::listenToKeys(ImGuiData &imGuiData)
{
    clients = new std::unordered_map<std::string*, Npc*>();
    // ----- SERVER SHIT
    boost::asio::io_context io_context;

    // Erstelle den Client
    Client client(io_context, "127.0.0.1", "12345", clients);

    // Hauptschleife, um Nachrichten zu senden
    std::thread io_thread([&io_context]()
                          { io_context.run(); });

    // ----- -----

    initAddresses();

    Npc *mainPlayer = new Npc(ADDR_PLAYERBASE);
    // OCNpc *mainPlayer = new OCNpc(*(void**)ADDR_PLAYERBASE);
    ZVec3 tempPosition;
    // std::vector<OCNpc*> listNpc;

    while (true)
    {
        Sleep(50);

        // Tp to Old Camp
        if (GetAsyncKeyState(VK_RSHIFT) < 0)
        {
            std::cout << "Pressed Shift! \n";

            Data data;
            data.id = 101;
            data.names.push_back(std::to_string(mainPlayer->getX()));
            data.names.push_back(std::to_string(mainPlayer->getZ()));
            data.names.push_back(std::to_string(mainPlayer->getY()));

            std::string bufferStr = data.serialize();
            client.send_message(bufferStr);
            Sleep(400);
            /*mainPlayer->setPlayerPosition(-10112.5f, 7768, -900);
            std::cout << "Teleported to Old Camp" << std::endl;*/
        }

        // Spawn NPC
        if (GetAsyncKeyState(VK_DELETE) < 0)
        {
            mainPlayer->oCNpc->getPositionWorld(&tempPosition);
            std::cout << tempPosition.getPos() << std::endl;

            Npc *npc = new Npc();
            npc->setCurrentHealth(10);
            npc->setMaxHealth(10);
            npc->oCNpc->setVisualWithString("HUMANS.MDS");
            npc->oCNpc->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);

            npc->oCNpc->enable(&tempPosition);
        }

        // Hide/Show Menu
        if (GetKeyState(VK_HOME) < 0)
        {
            imGuiData.toggleGuiVisibility();
            std::cout << "Pressed Home" << std::endl;
        }

        // Ejects the DLL
        if (GetAsyncKeyState(VK_END))
        {
            break;
        }

        // Sets or refreshes the Position of NPC's
        //setPositions();
        Sleep(100);
    }

    io_thread.join();
}