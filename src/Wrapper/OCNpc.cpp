#include "OCNpc.h"

struct OCObjectFactory {
    typedef void*(__thiscall * _CreateNPC)(void* pThis, int param);
    _CreateNPC createNpc;

    void* pThis = *(void**)0x82c114;
}oCObjectFactory;

void OCNpc::initializeFunctionPointers()
{
    oCObjectFactory.createNpc = (OCObjectFactory::_CreateNPC)(0x6c8560);

    oCNpcCtorRef = reinterpret_cast<_OCNpcCtor>(0x68b3d0);
    initModelRef = reinterpret_cast<_InitModel>(0x695020);
    setOnFloorRef = reinterpret_cast<_SetOnFloor>(0x6d43c0);
    setPositionWorldRef = reinterpret_cast<_SetPositionWorld>(0x5ee650);
    getPositionWorldRef = reinterpret_cast<_GetPositionWorld>(0x51b3c0);
    setVisualRef = reinterpret_cast<_SetVisual>(0x05d6e10);
    setVisualWithStringRef = reinterpret_cast<_SetVisualWithString>(0x5d6fa0);
    getVisualRef = reinterpret_cast<_GetVisual>(0x5e9a70);
    setVobIDRef = reinterpret_cast<_SetVobID>(0x5d3720);
    setStaticVobRef = reinterpret_cast<_SetStaticVob>(0x645000);
    setDrawBBox3DRef = reinterpret_cast<_SetDrawBBox3D>(0x645030);
    setPhysicsEnabledRef = reinterpret_cast<_SetPhysicsEnabled>(0x5efc20);
    addVobToWorldRef = reinterpret_cast<_AddVobToWorld>(0x5d74f0);
    enableRef = reinterpret_cast<_Enable>(0x6a2000);
    setAdditionalVisualsRef = reinterpret_cast<_SetAdditionalVisuals>(0x694ef0);
    setVobNameRef = reinterpret_cast<_SetVobName>(0x5d4970);
}

OCNpc::OCNpc(void *existingAddress) : pThis(existingAddress)
{
    if (!pThis)
        throw std::runtime_error("Invalid Memory-Address given over.");
    
    initializeFunctionPointers();
}

OCNpc::OCNpc()
{
    initializeFunctionPointers();
    createNewNpc();
    //pThis = createNewNpc();

}

uintptr_t OCNpc::getAddress2(){
    return reinterpret_cast<uintptr_t>(pThis);
}

void OCNpc::createNewNpc()
{
    pThis = (void*)oCObjectFactory.createNpc(oCObjectFactory.pThis, -1); //oCNpcCtorRef(this); //
    std::cout << "Pointer of NPC: " << pThis << std::endl;
    //return oCNpcCtorRef(this);
}

void OCNpc::setVisualWithString(char *visual){
    zSTRING *visualString = new zSTRING(visual);
    setVisualWithStringRef(pThis, visualString);
}

void OCNpc::setAdditionalVisuals(char * textureBody, int param2, int param3, char * textureHead, int param5, int param6, int param7){
    zSTRING *body = new zSTRING(textureBody);// "Sca_Body", hum_body_Naked0
    zSTRING *head = new zSTRING(textureHead);// "",         Hum_Head_Pony
    
    setAdditionalVisualsRef(pThis, body, param2, param3, head, param5, param6, param7);
}

void OCNpc::setVobName(char * vobName) {
    zSTRING *name = new zSTRING(vobName);

    setVobNameRef(pThis, name);
}

void OCNpc::enable(ZVec3 *pos)
{
    this->pos = new ZVec3();
    this->pos->initialize(pos->getPosX(), pos->getPosZ(), pos->getPosY() + 20);
    enableRef(pThis, pos);
}

void OCNpc::setPosition(const ZVec3 *position)
{

}

// Beispielmethode, um den NPC zu manipulieren
void OCNpc::getPositionWorld(ZVec3 *position)
{
    getPositionWorldRef(pThis, position);
}

/*    _Enable enableRef;
    _SetAdditionalVisuals setAdditionalVisualsRef;*/