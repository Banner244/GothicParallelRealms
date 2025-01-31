#include "zCModel.h"

zCModel::zCModel(void * pThis) : pThis(pThis){
    initializeFunctionPointers();
}

void zCModel::initializeFunctionPointers(){
    startAnimationRef = reinterpret_cast<_StartAnimation>(0x55ce40);
}

void zCModel::startAnimation(char * animName){
    zSTRING * animNameZStr = new zSTRING(animName);
    startAnimationRef(pThis, animNameZStr);
}

