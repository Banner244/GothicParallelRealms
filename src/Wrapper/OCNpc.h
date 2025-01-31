#pragma once

#include <iostream>

#include "ZVec3.h"
#include "zSTRING.h"
#include "zMAT4.h"

class OCNpc
{
public:
    using _OCNpcCtor = void *(__thiscall *)(void *pThis);
    using _InitModel = void(__thiscall *)(void *pThis);
    using _SetOnFloor = void *(__thiscall *)(void *pThis, ZVec3 *vec);
    using _SetPositionWorld = void(__thiscall *)(void *pThis, ZVec3 *param1);
    using _GetPositionWorld = void(__thiscall *)(void *pThis, ZVec3 *param1);
    using _SetVisual = void(__thiscall *)(void *pThis, void *visual);
    using _SetVisualWithString = void(__thiscall *)(void *pThis, zSTRING *visual);
    using _GetVisual = void *(__thiscall *)(void *pThis);
    using _SetStaticVob = void(__thiscall *)(void *pThis, int param1);
    using _SetDrawBBox3D = void(__thiscall *)(void *pThis, int param1);
    using _SetPhysicsEnabled = void(__thiscall *)(void *pThis, int param1);
    using _SetVobID = void(__thiscall *)(void *pThis, unsigned long ID);
    using _AddVobToWorld = void *(__thiscall *)(void *pThis);
    using _Enable = void(__thiscall *)(void *pThis, ZVec3 *param1);
    using _SetAdditionalVisuals = void(__thiscall *)(void *pThis, zSTRING *textureBody, int param2, int param3, zSTRING *textureHead, int param5, int param6, int param7);
    using _SetVobName = void(__thiscall *)(void *pThis, zSTRING *vobName);
    using _SetByScriptInstance = int(__thiscall *)(void *pThis, zSTRING *visual, int param2);
    using _BeginMovement = void(__thiscall *)(void *pThis);
    using _GetTrafoModelNodeToWorld = zMAT4*(__thiscall *)(void *pThis, zMAT4 * matrix, int param2);
    using _SetTrafo = void(__thiscall *)(void *pThis, zMAT4 * matrix);
    using _SetVobInMovement = void(__thiscall *)(void *pThis, int param1);
    using _Move = void(__thiscall *)(void *pThis, float x, float z, float y);
    using _GetModel = void*(__thiscall *)(void *pThis);
    using _ApplyOverlay = int(__thiscall *)(void *pThis, zSTRING *anim);

    // function-pointer for the methods of the NPCs
    _OCNpcCtor oCNpcCtorRef;
    _InitModel initModelRef;
    _SetOnFloor setOnFloorRef;
    _SetPositionWorld setPositionWorldRef;
    _GetPositionWorld getPositionWorldRef;
    _SetVisual setVisualRef;
    _SetVisualWithString setVisualWithStringRef;
    _GetVisual getVisualRef;
    _SetStaticVob setStaticVobRef;
    _SetDrawBBox3D setDrawBBox3DRef;
    _SetPhysicsEnabled setPhysicsEnabledRef;
    _SetVobID setVobIDRef;
    _AddVobToWorld addVobToWorldRef;
    _Enable enableRef;
    _SetAdditionalVisuals setAdditionalVisualsRef;
    _SetVobName setVobNameRef;
    _SetByScriptInstance setByScriptInstanceRef;
    _BeginMovement beginMovementRef;
    _GetTrafoModelNodeToWorld getTrafoModelNodeToWorldRef;
    _SetTrafo setTrafoRef;
    _SetVobInMovement setVobInMovementRef;
    _Move moveRef;
    _GetModel getModelRef;
    _ApplyOverlay applayOverlayRef;

private:
    void *pThis = nullptr; // Pointer to the NPC-Instance in memory
    ZVec3 *pos = nullptr;


public:
    // Constructor for the already existing Objekt
    OCNpc(void *existingAddress);

    // Konstruktor für neue Objekte
    OCNpc();

    // Method to initialise memory-addresses
    void initializeFunctionPointers();

    // Method to create a new NPC-Instance
    void createNewNpc();

    // returns pThis
    void *getAddress() const;

    uintptr_t getAddress2();


    void setVisualWithString(char *visual);

    void setAdditionalVisuals(char * textureBody, int param2, int param3, char * textureHead, int param5, int param6, int param7);

    void setVobName(char * vobName);

    void setByScriptInstance(char * name, int param2);

    void enable(ZVec3 *pos);

    void enableWithdCoords(float x, float z, float y);

    void setPosition(const ZVec3 *position);

    // Beispielmethode, um den NPC zu manipulieren
    void getPositionWorld(ZVec3 *position);

    void beginMovement();

    zMAT4* getTrafoModelNodeToWorld(zMAT4 * matrix, int param2);

    void setTrafo(zMAT4 * matrix);

    void setVobInMovement(int param);
    void move(float x, float z, float y);

    void* getModel();

    int applyOverlay(char * animName);

};
