#include "OCNpc.h"

struct OCObjectFactory
{
    typedef void *(__thiscall *_CreateNPC)(void *pThis, int param);
    _CreateNPC createNpc;

    void *pThis = *(void **)0x82c114;
} oCObjectFactory;

void OCNpc::initializeFunctionPointers()
{
    //oCObjectFactory.createNpc = (OCObjectFactory::_CreateNPC)(0x6c8560);

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
    setByScriptInstanceRef = reinterpret_cast<_SetByScriptInstance>(0x6a1bf0);
    beginMovementRef = reinterpret_cast<_BeginMovement>(0x5f0510);
    getTrafoModelNodeToWorldRef = reinterpret_cast<_GetTrafoModelNodeToWorld>(0x5d84d0);
    setTrafoRef = reinterpret_cast<_SetTrafo>(0x5ee6b0);
    setVobInMovementRef = reinterpret_cast<_SetVobInMovement>(0x5f0460);
    moveRef = reinterpret_cast<_Move>(0x5edde0);
    getModelRef = reinterpret_cast<_GetModel>(0x695300);
    applayOverlayRef = reinterpret_cast<_ApplyOverlay>(0x68ad40);
    setBodyStateRef = reinterpret_cast<_SetBodyState>(0x6b8000);
    initHumanAIRef = reinterpret_cast<_InitHumanAI>(0x68ce20);
    preSaveGameProcessingRef = reinterpret_cast<_PreSaveGameProcessing>(0x6a4500);
    setSleepingModeRef = reinterpret_cast<_SetSleepingMode>(0x5d7280);
    setSleepingRef = reinterpret_cast<_SetSleeping>(0x5d7250);
    addRefVobSubtreeRef = reinterpret_cast<_AddRefVobSubtree>(0x5d66f0);
    setVobPresentNameRef = reinterpret_cast<_SetVobPresentName>(0x5d3780);
    getVobPresentNameRef = reinterpret_cast<_GetVobPresentName>(0x5d3790);
    insertInVobListRef = reinterpret_cast<_InsertInVobList>(0x6b6f30);
}

/*OCNpc::OCNpc(void *existingAddress) : pThis(existingAddress)
{
    if (!pThis)
        throw std::runtime_error("Invalid Memory-Address given over.");

    initializeFunctionPointers();
    
}

OCNpc::OCNpc()
{
    initializeFunctionPointers();
    createNewNpc();
    // pThis = createNewNpc();
}*/

OCNpc * OCNpc::CreateNewNpc() // STATIC 
{
    oCObjectFactory.createNpc = (OCObjectFactory::_CreateNPC)(0x6c8560);
    OCNpc * npc = (OCNpc *)oCObjectFactory.createNpc(oCObjectFactory.pThis, -1);
    npc->initializeFunctionPointers();
    return npc;
}

OCNpc * OCNpc::CreateFromPointer(void* address) // STATIC 
{
    OCNpc * npc = reinterpret_cast<OCNpc*>(address);
    std::cout << "Address: " << npc << "\n";
    npc->initializeFunctionPointers();
    return npc;
}

void *OCNpc::getAddress()
{
    return static_cast<void*>(this);
}

uintptr_t OCNpc::getAddress2()
{
    return reinterpret_cast<uintptr_t>(this);
}

/*void OCNpc::createNewNpc()
{
    //pThis = oCNpcCtorRef(pThis);
    pThis = (void *)oCObjectFactory.createNpc(oCObjectFactory.pThis, -1); // oCNpcCtorRef(this); //
    std::cout << "Pointer of NPC: " << pThis << std::endl;
    // return oCNpcCtorRef(this);
}*/

void OCNpc::setVisualWithString(char *visual)
{
    zSTRING *visualString = new zSTRING(visual);
    setVisualWithStringRef(this, visualString);
}

void OCNpc::setAdditionalVisuals(char *textureBody, int param2, int param3, char *textureHead, int param5, int param6, int param7)
{
    zSTRING *body = new zSTRING(textureBody); // "Sca_Body", hum_body_Naked0
    zSTRING *head = new zSTRING(textureHead); // "",         Hum_Head_Pony

    setAdditionalVisualsRef(this, body, param2, param3, head, param5, param6, param7);
}

void OCNpc::setVobName(char *vobName)
{
    zSTRING *name = new zSTRING(vobName);
    setVobNameRef(this, name);
}

void OCNpc::setByScriptInstance(char *nameS, int param2)
{
    zSTRING *name = new zSTRING(nameS);
    setByScriptInstanceRef(this, name, param2);
}

void OCNpc::enable(ZVec3 *pos)
{
    this->pos = new ZVec3();
    this->pos->initialize(pos->getPosX(), pos->getPosZ(), pos->getPosY() + 20);
    enableRef(this, pos);
}

void OCNpc::enableWithdCoords(float x, float z, float y)
{
    this->pos = new ZVec3();
    this->pos->initialize(x, z, y);
    enableRef(this, pos);
}

void OCNpc::setPosition(const ZVec3 *position)
{
}

// Beispielmethode, um den NPC zu manipulieren
void OCNpc::getPositionWorld(ZVec3 *position)
{
    getPositionWorldRef(this, position);
}

void OCNpc::beginMovement()
{
    beginMovementRef(this);
}

zMAT4 *OCNpc::getTrafoModelNodeToWorld(zMAT4 *matrix, int param2)
{
    return getTrafoModelNodeToWorldRef(this, matrix, param2);
}

void OCNpc::setTrafo(zMAT4 *matrix)
{
    setTrafoRef(this, matrix);
}

void OCNpc::setVobInMovement(int param)
{
    setVobInMovementRef(this, param);
}

void OCNpc::move(float x, float z, float y)
{
    moveRef(this, x, z, y);
}

void *OCNpc::getModel()
{
    return getModelRef(this);
}

int OCNpc::applyOverlay(char *animName)
{
    zSTRING *name = new zSTRING(animName);
    return applayOverlayRef(this, name);
}

void OCNpc::setBodyState(int param1){
    setBodyStateRef(this, param1);
}

void OCNpc::initHumanAI() {
    initHumanAIRef(this);
}

void OCNpc::setSleepingMode(int param1) {
    setSleepingModeRef(this, param1);
}

void OCNpc::setSleeping(int param1) {
    setSleepingRef(this, param1);
}

void OCNpc::addRefVobSubtree(void * zCTree) {
    addRefVobSubtreeRef(this, zCTree);
}

void OCNpc::setStaticVob(int param) {
    setStaticVobRef(this, param);
}

void OCNpc::setVobPresentName(char * name) {
    zSTRING myName(name);
    setVobPresentNameRef(this, &myName);
}

zSTRING * OCNpc::getVobPresentName(){
    return getVobPresentNameRef(this);
}

void OCNpc::insertInVobList(void * vob){
    insertInVobListRef(this, vob);
}

/*    _Enable enableRef;
    _SetAdditionalVisuals setAdditionalVisualsRef;*/