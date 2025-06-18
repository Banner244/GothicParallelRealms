#include "OCNpc.h"

/*struct OCObjectFactory
{
    typedef void *(__thiscall *_CreateNPC)(void *pThis, int param);
    _CreateNPC createNpc;

    void *pThis = *(void **)0x82c114;
} oCObjectFactory;*/

OCNpc * OCNpc::CreateNewNpc() // STATIC 
{
    /*oCObjectFactory.createNpc = (OCObjectFactory::_CreateNPC)(0x6c8560);
    OCNpc * npc = (OCNpc *)oCObjectFactory.createNpc(oCObjectFactory.pThis, -1);*/
    OCNpc * npc = oCObjectFactory::CreateNpc();
    std::cout << "Pointer of NPC: " << npc << "\n";
    return npc;
}

OCNpc * OCNpc::CreateFromPointer(void* address) // STATIC 
{
    if (!address)
        throw std::runtime_error("Invalid Memory-Address given over.");

    return reinterpret_cast<OCNpc*>(address);
}

void OCNpc::setVisualWithString(char *visual)
{
    using _SetVisualWithString = void(__thiscall *)(void *pThis, zSTRING *visual);
    _SetVisualWithString setVisualWithStringRef = reinterpret_cast<_SetVisualWithString>(0x5d6fa0);

    zSTRING *visualString = zSTRING::CreateNewzSTRING(visual); //new zSTRING(visual);
    setVisualWithStringRef(this, visualString);
}

void OCNpc::setAdditionalVisuals(char *textureBody, int param2, int param3, char *textureHead, int param5, int param6, int param7)
{
    using _SetAdditionalVisuals = void(__thiscall *)(void *pThis, zSTRING *textureBody, int param2, int param3, zSTRING *textureHead, int param5, int param6, int param7);
    _SetAdditionalVisuals setAdditionalVisualsRef = reinterpret_cast<_SetAdditionalVisuals>(0x694ef0);

    zSTRING *body = zSTRING::CreateNewzSTRING(textureBody); //new zSTRING(textureBody); // "Sca_Body", hum_body_Naked0
    zSTRING *head = zSTRING::CreateNewzSTRING(textureHead); //new zSTRING(textureHead); // "",         Hum_Head_Pony

    setAdditionalVisualsRef(this, body, param2, param3, head, param5, param6, param7);
}

void OCNpc::setVobName(char *vobName)
{
    using _SetVobName = void(__thiscall *)(void *pThis, zSTRING *vobName);
    _SetVobName setVobNameRef = reinterpret_cast<_SetVobName>(0x5d4970);

    zSTRING *name = zSTRING::CreateNewzSTRING(vobName);// new zSTRING(vobName);
    setVobNameRef(this, name);
}

void OCNpc::setByScriptInstance(char *nameS, int param2)
{
    using _SetByScriptInstance = int(__thiscall *)(void *pThis, zSTRING *visual, int param2);
    _SetByScriptInstance setByScriptInstanceRef = reinterpret_cast<_SetByScriptInstance>(0x6a1bf0);

    zSTRING *name = zSTRING::CreateNewzSTRING(nameS);//new zSTRING(nameS);
    setByScriptInstanceRef(this, name, param2);
}

void OCNpc::enable(ZVec3 *pos)
{
    using _Enable = void(__thiscall *)(void *pThis, ZVec3 *param1);
    _Enable enableRef = reinterpret_cast<_Enable>(0x6a2000);
    //this->pos = new ZVec3();
    //this->pos->initialize(pos->getPosX(), pos->getPosZ(), pos->getPosY() + 20);
    enableRef(this, pos);
}

void OCNpc::enableWithdCoords(float x, float z, float y)
{
    ZVec3 * tPos = new ZVec3();
    tPos->initialize(x, z, y);
    enable(tPos);
}

void OCNpc::setPosition(const ZVec3 *position)
{
}

void OCNpc::getPositionWorld(ZVec3 *position)
{
    using _GetPositionWorld = void(__thiscall *)(void *pThis, ZVec3 *param1);
    _GetPositionWorld getPositionWorldRef = reinterpret_cast<_GetPositionWorld>(0x51b3c0);

    getPositionWorldRef(this, position);
}

void OCNpc::beginMovement()
{
    using _BeginMovement = void(__thiscall *)(void *pThis);
    _BeginMovement beginMovementRef = reinterpret_cast<_BeginMovement>(0x5f0510);
    beginMovementRef(this);
}

zMAT4 *OCNpc::getTrafoModelNodeToWorld(zMAT4 *matrix, int param2)
{
    using _GetTrafoModelNodeToWorld = zMAT4*(__thiscall *)(void *pThis, zMAT4 * matrix, int param2);
    _GetTrafoModelNodeToWorld getTrafoModelNodeToWorldRef = reinterpret_cast<_GetTrafoModelNodeToWorld>(0x5d84d0);

    return getTrafoModelNodeToWorldRef(this, matrix, param2);
}

void OCNpc::setTrafo(zMAT4 *matrix)
{
    using _SetTrafo = void(__thiscall *)(void *pThis, zMAT4 * matrix);
    _SetTrafo setTrafoRef = reinterpret_cast<_SetTrafo>(0x5ee6b0);

    setTrafoRef(this, matrix);
}

void OCNpc::setVobInMovement(int param)
{
    using _SetVobInMovement = void(__thiscall *)(void *pThis, int param1);
    _SetVobInMovement setVobInMovementRef = reinterpret_cast<_SetVobInMovement>(0x5f0460);

    setVobInMovementRef(this, param);
}

void OCNpc::move(float x, float z, float y)
{
    using _Move = void(__thiscall *)(void *pThis, float x, float z, float y);
    _Move moveRef = reinterpret_cast<_Move>(0x5edde0);

    moveRef(this, x, z, y);
}

void *OCNpc::getModel()
{
    using _GetModel = void*(__thiscall *)(void *pThis);
    _GetModel getModelRef = reinterpret_cast<_GetModel>(0x695300);

    return getModelRef(this);
}

void * OCNpc::getHomeWorld(){
    using _GetHomeWorld = void*(__thiscall *)(void *pThis);
    _GetHomeWorld getHomeWorldRef = reinterpret_cast<_GetHomeWorld>(0x73f4d0);

    return getHomeWorldRef(this);
}

float OCNpc::getDistanceToVob(void * vob){
    using _GetDistanceToVob = float(__thiscall *)(void *pThis, void * vob);
    _GetDistanceToVob getDistanceToVobRef = reinterpret_cast<_GetDistanceToVob>(0x5ee400);

    return getDistanceToVobRef(this, vob);
}

void OCNpc::insertInVobList(void * vob){
    using _InsertInVobList = void(__thiscall *)(void *pThis, void * vob);
    _InsertInVobList insertInVobListRef = reinterpret_cast<_InsertInVobList>(0x6b6f30);
    insertInVobListRef(this, vob);
}

zSTRING * OCNpc::getSectorNameVobIsIn(){
    using _GetSectorNameVobIsIn = zSTRING*(__thiscall *)(void *pThis);
    _GetSectorNameVobIsIn getSectorNameVobIsInRef = reinterpret_cast<_GetSectorNameVobIsIn>(0x5d5690);

    return getSectorNameVobIsInRef(this);
}

void OCNpc::addVobToWorld_CorrectParentDependencies(){
    using _AddVobToWorld_CorrectParentDependencies = void(__thiscall *)(void *pThis);
    _AddVobToWorld_CorrectParentDependencies addVobToWorld_CorrectParentDependenciesRef = reinterpret_cast<_AddVobToWorld_CorrectParentDependencies>(0x5d74f0);

    addVobToWorld_CorrectParentDependenciesRef(this);
}

oCItem * OCNpc::getEquippedArmor() {
    using _GetEquippedArmor = oCItem*(__thiscall *)(void *pThis);
    _GetEquippedArmor getEquippedArmorRef = reinterpret_cast<_GetEquippedArmor>(0x6947a0);

    return getEquippedArmorRef(this);
}

oCItem * OCNpc::getEquippedMeleeWeapon(){
    using _GetEquippedMeleeWeapon = oCItem*(__thiscall *)(void *pThis);
    _GetEquippedMeleeWeapon getEquippedMeleeWeaponRef = reinterpret_cast<_GetEquippedMeleeWeapon>(0x694580);

    return getEquippedMeleeWeaponRef(this);
}

oCItem * OCNpc::getEquippedRangedWeapon(){
    using _GetEquippedRangedWeapon = oCItem*(__thiscall *)(void *pThis);
    _GetEquippedRangedWeapon getEquippedRangedWeaponRef = reinterpret_cast<_GetEquippedRangedWeapon>(0x694690);

    return getEquippedRangedWeaponRef(this);
}

void OCNpc::equipArmor(oCItem * armor)
{
    using _EquipArmor = void(__thiscall *)(void *pThis, oCItem * armor);
    _EquipArmor equipArmorRef = reinterpret_cast<_EquipArmor>(0x697080);
    equipArmorRef(this, armor);
}

void OCNpc::equipItem(oCItem * item)
{
    using _EquipItem = void(__thiscall *)(void *pThis, oCItem * item);
    _EquipItem equipItemRef = reinterpret_cast<_EquipItem>(0x68f940);
    equipItemRef(this, item);
}

void OCNpc::equip(oCItem * item)
{
    using _Equip = void(__thiscall *)(void *pThis, oCItem * item);
    _Equip equipRef = reinterpret_cast<_Equip>(0x6968f0);
    equipRef(this, item);
}

void OCNpc::equipWeapon(oCItem * weapon)
{
    using _EquipItem = void(__thiscall *)(void *pThis, oCItem * item);
    _EquipItem equipItemRef = reinterpret_cast<_EquipItem>(0x696c20);
    equipItemRef(this, weapon);
}

void OCNpc::equipBestWeapon(int param1)
{
    using _EquipBestWeapon = void(__thiscall *)(void *pThis, int param1);
    _EquipBestWeapon equipBestWeaponRef = reinterpret_cast<_EquipBestWeapon>(0x6aa220);
    equipBestWeaponRef(this, param1);
}

void OCNpc::equipFarWeapon(oCItem * weapon)
{
    using _EquipItem = void(__thiscall *)(void *pThis, oCItem * item);
    _EquipItem equipItemRef = reinterpret_cast<_EquipItem>(0x696f00);
    equipItemRef(this, weapon);
}

void OCNpc::unequipItem(oCItem * item)
{
    using _UnequipItem = void(__thiscall *)(void *pThis, oCItem * item);
    _UnequipItem unequipItemRef = reinterpret_cast<_UnequipItem>(0x68fbc0);
    unequipItemRef(this, item);
}


oCItem * OCNpc::putInInv(oCItem * item)
{
    using _PutInInv = oCItem*(__thiscall *)(void *pThis, oCItem * item);
    _PutInInv putInInvRef = reinterpret_cast<_PutInInv>(0x6a4ff0);

    return putInInvRef(this, item);

}

int OCNpc::EV_DrawWeapon1(oCMsgWeapon * msgWeapon)
{
    using _EV_DrawWeapon1 = int(__thiscall *)(void *pThis, oCMsgWeapon * msgWeapon);
    _EV_DrawWeapon1 EV_DrawWeapon1Ref = reinterpret_cast<_EV_DrawWeapon1>(0x6a8b80);

    return EV_DrawWeapon1Ref(this, msgWeapon);
}

// returns the weapon in the fighting slot
oCItem * OCNpc::getWeapon()
{
    using _GetWeapon = oCItem*(__thiscall *)(void *pThis);
    _GetWeapon getWeaponRef = reinterpret_cast<_GetWeapon>(0x6943f0);

    return getWeaponRef(this);
}

int OCNpc::useItem(oCItem * item)
{
    using _UseItem = int(__thiscall *)(void *pThis, oCItem * item);
    _UseItem useItemRef = reinterpret_cast<_UseItem>(0x698810);

    return useItemRef(this, item);
}

void OCNpc::setTalentValue(int talentIndex, int value)
{
    using _SetTalentValue = void(__thiscall *)(void *pThis, int talentIndex, int value);
    _SetTalentValue setTalentValueRef = reinterpret_cast<_SetTalentValue>(0x68e370);
    setTalentValueRef(this, talentIndex, value);
}

/*zSTRING *OCNpc::getName2(){
    zSTRING * nS = zSTRING::CreateNewzSTRING("");
    using _GetName = zSTRING* (__thiscall *)(void* pThis);
    _GetName getNameRef = reinterpret_cast<_GetName>(0x68D0B0);
    return getNameRef(this);

    //zSTRING* namePtr = (zSTRING*)((char*)this + 0x108);
    //return namePtr;
}*/
/*int OCNpc::applyOverlay(char *animName)
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



/*    _Enable enableRef;
    _SetAdditionalVisuals setAdditionalVisualsRef;*/