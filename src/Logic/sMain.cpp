#include "sMain.h"

sMain::sMain(){
	InitTrainer();
}

void sMain::InitTrainer() {
	player = new Player();
}


struct OCGameRef{
    typedef void(__thiscall * _Func)(void* pThis);
    _Func pause;
    _Func unPause;
    _Func init;

    typedef void(__thiscall * _FuncOneParam)(void* pThis, bool param);
    _FuncOneParam openSaveScreen;


    typedef int(__thiscall * _RetFunc)(void* pThis);
    _RetFunc getShowPlayerStatus;
    _RetFunc getDrawWaynet;

    
    typedef int(__thiscall * _RetFunc2)(void* pThis, int enumNumber);
    _RetFunc2 openView;

    typedef void*(__thiscall * _GetSpawnManager)(void* pThis);
    _GetSpawnManager getSpawnManager;

    typedef void*(__thiscall * _EnterWorld)(void* pThis, void *npc, int param_2, zSTRING * str);
    _EnterWorld enterWorld;

    void* pThis = *(void**)0x8DA6BC; // Adresse von oCGame
}oCGame;

struct OCNpc{
    typedef void*(__thiscall * _InitModel)(void* pThis);
    _InitModel initModel;

    typedef void*(__thiscall * _SetOnFloor)(void* pThis, ZVec3 * vec);
    _SetOnFloor setOnFloor;

    typedef void(__thiscall *_SetPositionWorld)(void *pThis, ZVec3 * param1);
    _SetPositionWorld tSetPositionWorld;

    typedef void(__thiscall *_GetPositionWorld)(void *pThis, ZVec3 * param1);
    _GetPositionWorld getPositionWorld;


    void* pThis = *(void**) 0x8DBBB0; // Adresse von 
}oNpc;


struct OCSpawnManagerRef{
    bool isSpawningEnabled;

    typedef void(__thiscall * _SummonNpc)(void* pThis, int param1, ZVec3 * coords, float param3);
    _SummonNpc summonNpc;

    typedef void(__thiscall * _SpawnImmediately)(void* pThis, int param1);
    _SpawnImmediately spawnImmediately;
    typedef void(__thiscall * _SpawnNpcVec)(void* pThis, void *npc, ZVec3 * coords, float param3);
    _SpawnNpcVec spawnNpcVec;
    typedef void(__thiscall * _SpawnNpcString)(void* pThis, void *npc, zSTRING * coords, float param3);
    _SpawnNpcString spawnNpcString;


    // Getting the base address of oCGame and adding offset to turn it into oCSpawnManager
    void* pThis = *(void**)(((uintptr_t)oCGame.pThis) + 0x134);
    // spawn func 
    //void* pThis = *(void**) (0x8DA6BC + 0x134); // Adresse von oCSpawnManager (894a04) 0x54ebe0  0x6373d3
}oCSpawnManager;

struct ZCViewRef{
    typedef void(__thiscall * _PrintMessage)(void* pThis, zSTRING *param_1, zSTRING *param_2,float param_3, ZCOLOR *param_4);
    _PrintMessage printMessage;

    typedef void(__thiscall * _PrintTimed)(void* pThis, int param_1,int param_2,zSTRING *param_3,float param_4, ZCOLOR *param_5);
    _PrintTimed printTimed;

    typedef void(__thiscall * _Printwin)(void* pThis, zSTRING *str);
    _Printwin printwin;

    typedef void(__thiscall * _Open)(void* pThis);
    _Open open;

    void* pThis = *(void**)0x8de1bc; // Adresse von CView
}zCViewRef;


struct OCObjectFactory {
    typedef void*(__thiscall * _CreateNPC)(void* pThis, int param);
    _CreateNPC createNpc;

    void* pThis = *(void**)0x82c114;
}oCObjectFactory;

void initAddresses() {
// Reverse  engineering zSTRING and calling the print function!

    oNpc.initModel = (OCNpc::_InitModel)(0x695020);
    oNpc.setOnFloor = (OCNpc::_SetOnFloor)(0x6d43c0);
    oNpc.tSetPositionWorld = (OCNpc::_SetPositionWorld)(0x5ee650);
    oNpc.getPositionWorld = (OCNpc::_GetPositionWorld)(0x51b3c0);

    oCObjectFactory.createNpc = (OCObjectFactory::_CreateNPC)(0x6c8560);

    oCSpawnManager.isSpawningEnabled = *(bool*)((uintptr_t)oCSpawnManager.pThis + 0xC);
    /* NPC SPAWN INIT */
    oCSpawnManager.spawnNpcVec = (OCSpawnManagerRef::_SpawnNpcVec)((0x6d0710));
    oCSpawnManager.spawnImmediately = (OCSpawnManagerRef::_SpawnImmediately)((0x6cf800));
    oCSpawnManager.spawnNpcString = (OCSpawnManagerRef::_SpawnNpcString)((0x6d04c0));

    oCSpawnManager.summonNpc = (OCSpawnManagerRef::_SummonNpc)((0x6d0350));

    //oCSpawnManager =  638b50
    //oCGame.getSpawnManager = (OCGameRef::_GetSpawnManager)(oCGame.pThis + 0x134); //(OCGameRef::_GetSpawnManager)(0x638b50);



    globalFunction.printDebug = (GlobalFunctions::_PrintDebug)(0x645280);
    globalFunction.stdPrintWin = (GlobalFunctions::_StdPrintwin)(0x6fc420);

    globalFunction.print = (GlobalFunctions::_Print)(0x756e00); // Nothing happens ...

    zCViewRef.open = (ZCViewRef::_Open)(0x006fd070); // does something...

    zCViewRef.printwin = (ZCViewRef::_Printwin)((0x700d20)); // No crash but no result...
    zCViewRef.printTimed = (ZCViewRef::_PrintTimed)((0x6fe1a0)); // No crash but no result...
    zCViewRef.printMessage = (ZCViewRef::_PrintMessage)(0x6fe5c0);

    // Work
    globalFunction.openCheatConsole = (GlobalFunctions::_CheatConsole)(0x647129);
    oCGame.pause = (OCGameRef::_Func)( 0x7dcc48);
    //oCGame.unPause = (CCGameRef::_Func)( (*(DWORD*)0x7dcc4c));
    //oCGame.openSaveScreen = (CCGameRef::_FuncOneParam)( (*(DWORD*)0x7dcc88));
    //oCGame.getDrawWaynet = (CCGameRef::_RetFunc) ((*(DWORD*)0x7dcc54));

    //oCGame.init = (CCGameRef::_Func)( (*(DWORD*)0x7dcbf4)); // works ??

    // Do not work
    //oCGame.getShowPlayerStatus = (CCGameRef::_RetFunc) ((*(DWORD*)0x8DA6BC + 0x9c) );
    oCGame.openView = (OCGameRef::_RetFunc2)(0x425d4d);

    oCGame.enterWorld = (OCGameRef::_EnterWorld)(0x63ead0);
}


void sMain::listenToKeys(ImGuiData &imGuiData){
    initAddresses();
    
	zSTRING myString;
    		myString.initialize("VLK_502_BUDDLER");
			std::cout << "zSTRING: " << myString.getStr() << std::endl;

    // In GOTHIC: X; Z; Y
    ZVec3 vec;

            float posx = -10112.5f;//4350;
            float posz = -900;//6048;
            float posy = 7768;//28454;
            vec.initialize(posx, posz, posy);
            //vec.initialize(player->getX(), player->getZ(), player->getY());
            std::cout << "Vec Init: " << vec.getPos() << std::endl;    

    ZCOLOR color;
    //OCSpawnManager spanwManager;

	while (true) {
		Sleep(50);

        if(GetAsyncKeyState(VK_RSHIFT) < 0) {
            player->setPlayerPosition(-10112.5f, 7768, -900);
        }

		if (GetAsyncKeyState(VK_DELETE) < 0){
            ZVec3 temp;
            oNpc.getPositionWorld(oNpc.pThis, &temp);

            std::cout << "Vec Player OCNPC Getter: " << temp.getPos() << std::endl;    

            //oCSpawnManager.spawnImmediately(oCSpawnManager.pThis, 1);
            //std::cout << "IsSpawningEnabled: " << oCSpawnManager.isSpawningEnabled<< std::endl;
            void *test = oCObjectFactory.createNpc(oCObjectFactory.pThis, -1);
            
            //oNpc.setOnFloor(test, &temp);

            //oCSpawnManager.spawnNpcString(oCSpawnManager.pThis, newNpc, &myString, 0.0);
            //oCSpawnManager.spawnNpcVec(oCSpawnManager.pThis, test, &temp, 0.0f);
            //oCSpawnManager.spawnImmediately(oCSpawnManager.pThis, 1);

            //oNpc.initModel(test);
            //oNpc.getPositionWorld(test, &temp);
            oCGame.enterWorld(oCGame.pThis, test, 0, &myString);
            std::cout << "Ob. Factory: " << temp.getPos() << std::endl;    

            //oCSpawnManager.summonNpc(oCSpawnManager.pThis, -1, &vec, 0.0f);

            //spanwManager.initialize();
            //std::cout << "spanwManager: SUCCESS"  << std::endl; 
            //spanwManager.spawnImmediately(1);
            //oCSpawnManager.spawnImmediately(oCSpawnManager.pThis, 1);

            //spanwManager.spawnNpcVec(oNpc.pThis, &vec, 0.0f);

            //zCViewRef.printwin(zCViewRef.pThis, &myString);
            //zCViewRef.printTimed(zCViewRef.pThis, 100, 300, &myString, 3000.0f, &color);
            //zCViewRef.printMessage(zCViewRef.pThis, &myString, &myString, 3000.0f, &color);
            Sleep(100);
		}



		if (GetKeyState(VK_HOME) < 0){
			imGuiData.toggleGuiVisibility();
			std::cout << "PRessed Home" << std::endl;
			Sleep(100);
		}


		if (GetAsyncKeyState(VK_END)) {
			break;
		}
	}
}