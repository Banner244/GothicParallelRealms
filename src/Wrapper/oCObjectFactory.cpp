#include "oCObjectFactory.h"
/*struct OCObjectFactory
{
    typedef void *(__thiscall *_CreateNPC)(void *pThis, int param);
    _CreateNPC createNpc;

    void *pThis = *(void **)0x82c114;
} oCObjectFactory;*/

OCNpc * oCObjectFactory::CreateNpc() // STATIC
{
     using _CreateNPC = OCNpc*(__thiscall *)(void *pThis, int param);
    _CreateNPC createNpcRef = reinterpret_cast<_CreateNPC>(0x6c8560);

    return createNpcRef(getOCObjectFactoryAddress(), -1);
}

oCItem * oCObjectFactory::CreateItem(int scriptId) // STATIC
{
     using _CreateItem = oCItem*(__thiscall *)(void *pThis, int param);
    _CreateItem createItemRef = reinterpret_cast<_CreateItem>(0x6c8660);

    return createItemRef(getOCObjectFactoryAddress(), scriptId);
}


void * oCObjectFactory::getOCObjectFactoryAddress(){// STATIC
    return *(void **)0x82c114;
}