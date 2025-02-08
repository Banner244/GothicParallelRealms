#include "zCModel.h"

zCModel::zCModel(void * pThis) : pThis(pThis){
    initializeFunctionPointers();
}

void zCModel::initializeFunctionPointers(){
    startAnimationRef = reinterpret_cast<_StartAnimation>(0x55ce40);
    isAnimationActiveRef = reinterpret_cast<_IsAnimationActive>(0x55cef0);
    stopAnimationRef = reinterpret_cast<_StopAnimation>(0x55ce50);
    stopAnimationIntRef = reinterpret_cast<_StopAnimationInt>(0x560e10);
    startAniRef = reinterpret_cast<_StartAni>(0x5612f0);
    startAniIntRef = reinterpret_cast<_StartAniInt>(0x5612a0);
    getAniFromAniIDRef = reinterpret_cast<_GetAniFromAniID>(0x46d1e0);
    searchAniINdexRef = reinterpret_cast<_SearchAniIndex>(0x56f850);
    getActiveAniRef = reinterpret_cast<_GetActiveAni>(0x560d90);
}

void *zCModel::getAddress() const
{
    return pThis;
}

void zCModel::startAnimation(char * animName){
    zSTRING * animNameZStr = new zSTRING(animName);
    startAnimationRef(pThis, animNameZStr);
}

int zCModel::isAnimationActive(char * animName){
    zSTRING * animNameZStr = new zSTRING(animName);
    return isAnimationActiveRef(pThis, animNameZStr);
}

void zCModel::stopAnimation(char * animName){
    zSTRING * animNameZStr = new zSTRING(animName);
    stopAnimationRef(pThis, animNameZStr);
}

void zCModel::stopAnimationInt(int id){
    stopAnimationIntRef(pThis, id);
}

void zCModel::startAni(void * zcModelAni, int frame){
    startAniRef(pThis, zcModelAni, frame);
}
void zCModel::startAniInt(int id, int frame){
    startAniIntRef(pThis, id, frame);
}
void * zCModel::getAniFromAniID(int id){
    return getAniFromAniIDRef(pThis, id);
}

int zCModel::SearchAniIndex(char * aniName){
    zSTRING * aniNameZ = new zSTRING(aniName);
    return searchAniINdexRef(aniNameZ);
}

void * zCModel::getActiveAni(int id){
    return getActiveAniRef(pThis, id);
}