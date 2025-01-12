#include "sMain.h"
#include <vector>
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

/*struct OCNpc{
    typedef void(__thiscall * _InitModel)(void* pThis);
    _InitModel initModel;

    typedef void*(__thiscall * _SetOnFloor)(void* pThis, ZVec3 * vec);
    _SetOnFloor setOnFloor;

    typedef void(__thiscall *_SetPositionWorld)(void *pThis, ZVec3 * param1);
    _SetPositionWorld tSetPositionWorld;

    typedef void(__thiscall *_GetPositionWorld)(void *pThis, ZVec3 * param1);
    _GetPositionWorld getPositionWorld;

    typedef void(__thiscall *_SetVisual)(void *pThis, void * visual);
    _SetVisual setVisual;

    typedef void(__thiscall *_SetVisualWithString)(void *pThis, zSTRING * visual);
    _SetVisualWithString setVisualWithString;

    typedef void*(__thiscall * _GetVisual)(void* pThis);
    _GetVisual getVisual;

     typedef void(__thiscall * _SetStaticVob)(void* pThis, int param1); // param1 = 1
    _SetStaticVob setStaticVob;

    typedef void(__thiscall * _SetDrawBBox3D)(void* pThis, int param1); // param1 = 1
    _SetDrawBBox3D setDrawBBox3D;

    typedef void(__thiscall * _SetPhysicsEnabled)(void* pThis, int param1); // param1 = 1
    _SetPhysicsEnabled setPhysicsEnabled;

    typedef void(__thiscall * _SetVobID)(void* pThis, unsigned long ID);
    _SetVobID setVobID;

    typedef void*(__thiscall * _AddVobToWorld)(void* pThis);
    _AddVobToWorld addVobToWorld;

    typedef void(__thiscall *_Enable)(void *pThis, ZVec3 * param1);
    _Enable enable;

    typedef void(__thiscall *_SetAdditionalVisuals)(void *pThis, zSTRING * textureBody, int param2, int param3, zSTRING * textureHead, int param5, int param6, int param7);
    _SetAdditionalVisuals setAdditionalVisuals;

    void* pThis = *(void**) 0x8DBBB0; // Adresse vom Player
}oNpc;*/

struct OCWorldRef {

    typedef void(__thiscall *_AddVob)(void *pThis, void * vobParam);
    _AddVob addVob;

     typedef unsigned long(__thiscall *_GetVobHashIndex)(void *pThis, void * vobParam);
    _GetVobHashIndex getVobHashIndex;

    typedef void(__thiscall *_PrintStatus)(void *pThis);
    _PrintStatus printStatus;

    void* pThis = *(void**)(((uintptr_t)oCGame.pThis) + 0x8c);  // WORKS TOO
}oCWorldRef;


struct OCSpawnManagerRef{
    typedef void*(__thiscall * _SummonNpc)(void* pThis, int param1, ZVec3 * coords, float param3);
    _SummonNpc summonNpc;

    typedef void(__thiscall * _SpawnImmediately)(void* pThis, int param1);
    _SpawnImmediately spawnImmediately;
    typedef void(__thiscall * _SpawnNpcVec)(void* pThis, void *npc, ZVec3 * coords, float param3);
    _SpawnNpcVec spawnNpcVec;
    typedef void(__thiscall * _SpawnNpcString)(void* pThis, void *npc, zSTRING * coords, float param3);
    _SpawnNpcString spawnNpcString;

    // Getting the base address of oCGame and adding offset to turn it into oCSpawnManager
    void* pThis = *(void**)(((uintptr_t)oCGame.pThis) + 0x134);
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




void initAddresses() {
    oCWorldRef.addVob = (OCWorldRef::_AddVob)(0x5f6340);
    oCWorldRef.getVobHashIndex = (OCWorldRef::_GetVobHashIndex)(0x5f9720);
    oCWorldRef.printStatus = (OCWorldRef::_PrintStatus)(0x5f6bf0);

    /*oNpc.initModel = (OCNpc::_InitModel)(0x695020);
    oNpc.setOnFloor = (OCNpc::_SetOnFloor)(0x6d43c0);
    oNpc.tSetPositionWorld = (OCNpc::_SetPositionWorld)(0x5ee650);
    oNpc.getPositionWorld = (OCNpc::_GetPositionWorld)(0x51b3c0);
    oNpc.setVisual = (OCNpc::_SetVisual)(0x05d6e10);
    oNpc.setVisualWithString = (OCNpc::_SetVisualWithString)(0x5d6fa0);
    oNpc.getVisual = (OCNpc::_GetVisual)(0x5e9a70);
    oNpc.setVobID = (OCNpc::_SetVobID)(0x5d3720);
    oNpc.setStaticVob = (OCNpc::_SetStaticVob)(0x645000);
    oNpc.setDrawBBox3D = (OCNpc::_SetDrawBBox3D)(0x645030);
    oNpc.setPhysicsEnabled = (OCNpc::_SetPhysicsEnabled)(0x5efc20);
    oNpc.addVobToWorld = (OCNpc::_AddVobToWorld)(0x5d74f0);
    oNpc.enable = (OCNpc::_Enable)(0x6a2000);
    oNpc.setAdditionalVisuals = (OCNpc::_SetAdditionalVisuals)(0x694ef0);*/

    

    oCSpawnManager.spawnNpcVec = (OCSpawnManagerRef::_SpawnNpcVec)((0x6d0710));
    oCSpawnManager.spawnImmediately = (OCSpawnManagerRef::_SpawnImmediately)((0x6cf800));
    oCSpawnManager.spawnNpcString = (OCSpawnManagerRef::_SpawnNpcString)((0x6d04c0));
    oCSpawnManager.summonNpc = (OCSpawnManagerRef::_SummonNpc)((0x6d0350));

    zCViewRef.open = (ZCViewRef::_Open)(0x006fd070); // does something...
    zCViewRef.printwin = (ZCViewRef::_Printwin)((0x700d20)); 
    zCViewRef.printTimed = (ZCViewRef::_PrintTimed)((0x6fe1a0)); 
    zCViewRef.printMessage = (ZCViewRef::_PrintMessage)(0x6fe5c0);

    oCGame.pause = (OCGameRef::_Func)( 0x7dcc48);
    oCGame.unPause = (OCGameRef::_Func)( (*(DWORD*)0x7dcc4c));
    oCGame.openSaveScreen = (OCGameRef::_FuncOneParam)( (*(DWORD*)0x7dcc88));
    oCGame.getDrawWaynet = (OCGameRef::_RetFunc) ((*(DWORD*)0x7dcc54));
    oCGame.init = (OCGameRef::_Func)( (*(DWORD*)0x7dcbf4)); 
    oCGame.openView = (OCGameRef::_RetFunc2)(0x425d4d);
    oCGame.enterWorld = (OCGameRef::_EnterWorld)(0x63ead0);

    globalFunction.printDebug = (GlobalFunctions::_PrintDebug)(0x645280);
    globalFunction.stdPrintWin = (GlobalFunctions::_StdPrintwin)(0x6fc420);
    globalFunction.print = (GlobalFunctions::_Print)(0x756e00);
    globalFunction.openCheatConsole = (GlobalFunctions::_CheatConsole)(0x647129);
}

void sMain::listenToKeys(ImGuiData &imGuiData){
    initAddresses();

    OCNpc *mainPlayer = new OCNpc(*(void**)ADDR_PLAYERBASE);
    ZVec3 tempPosition;
    //std::vector<OCNpc*> listNpc;

	while (true) {
		Sleep(50);

        // Tp to Old Camp
        if(GetAsyncKeyState(VK_RSHIFT) < 0) {
            player->setPlayerPosition(-10112.5f, 7768, -900);
        }

        // Spawn dead Scavenger
		if (GetAsyncKeyState(VK_DELETE) < 0){
            /*oNpc.getPositionWorld(oNpc.pThis, &tempPosition);
            void *test = oCObjectFactory.createNpc(oCObjectFactory.pThis, -1);

            oNpc.setVisualWithString(test, &modelName);
            oNpc.setAdditionalVisuals(test, &body, 0, 0, &head, 0, 0, -1);
            oNpc.enable(test, &tempPosition);*/

           
            mainPlayer->getPositionWorld(&tempPosition);
            std::cout << tempPosition.getPos() << std::endl;

            OCNpc *someOne = new OCNpc();//(OCNpc*)oCObjectFactory.createNpc(oCObjectFactory.pThis, -1);

            Npc *npc = new Npc(someOne->getAddress2());
            npc->setMaxHealth(10);
            npc->setCurrentHealth(10);
            
            someOne->setVobName("SomeOne");
            someOne->setVisualWithString("HUMANS.MDS");
            //someOne->setAdditionalVisuals(&body, 0, 0, &head, 0, 0, -1); // scav.
            someOne->setAdditionalVisuals("hum_body_Naked0", 9, 0, "Hum_Head_Pony", 2, 0, -1);

            someOne->enable(&tempPosition);

            std::cout << "Successfully Spawned!" << std::endl;

            Sleep(100);
		}

        // Hide/Show Menu
		if (GetKeyState(VK_HOME) < 0){
			imGuiData.toggleGuiVisibility();
			std::cout << "Pressed Home" << std::endl;
			Sleep(100);
		}

        // Ejects the DLL
		if (GetAsyncKeyState(VK_END)) {
			break;
		}
	}
}