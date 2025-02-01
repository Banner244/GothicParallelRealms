#include "zCModel.h"

zCModel::zCModel(void * pThis) : pThis(pThis){
    initializeFunctionPointers();
}

void zCModel::initializeFunctionPointers(){
    startAnimationRef = reinterpret_cast<_StartAnimation>(0x55ce40);
    isAnimationActiveRef = reinterpret_cast<_IsAnimationActive>(0x55cef0);
    stopAnimationRef = reinterpret_cast<_StopAnimation>(0x55ce50);
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