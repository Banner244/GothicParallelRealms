#include "oCItem.h"

oCItem * oCItem::CreateoCItem(int itemId){
    /*void* raw = ::operator new(0x2fc); // Thas the size of 0CItem

    using _CTor = oCItem*(__thiscall *)(void *pThis);
    _CTor ctor = reinterpret_cast<_CTor>(0x00670de0);
     ctor(raw);

    return reinterpret_cast<oCItem*>(raw);*/
    oCItem * item = oCObjectFactory::CreateItem(itemId);
    return item;
}

void oCItem::initByScript(int id, int ka)
{
    using _InitByScript = void(__thiscall *)(void *pThis, int param1, int param2);
    _InitByScript initByScriptRef = reinterpret_cast<_InitByScript>(0x671660);

    initByScriptRef(this, id, ka);
}

int oCItem::setByScriptInstance(const char * name)
{
    using _SetByScriptInstance = int(__thiscall *)(void *pThis, zSTRING * instanceName, int param2);
    _SetByScriptInstance setByScriptInstanceRef = reinterpret_cast<_SetByScriptInstance>(0x6731b0);

    zSTRING * s = zSTRING::CreateNewzSTRING(name);
    return setByScriptInstanceRef(this, s, -1);
}

void oCItem::setName(std::string name)
{
	basic_string * n =  (basic_string*)((char*)this + 0x108);
	*n = name.c_str();
}

std::string oCItem::getName()
{
	basic_string * n =  (basic_string*)((char*)this + 0x108);
	return n->c_str();
}

zSTRING * oCItem::getInstanceName()
{
    zSTRING * name = zSTRING::CreateNewzSTRING("");
    using _GetInstanceName = zSTRING*(__thiscall *)(void *pThis, zSTRING* name);
    _GetInstanceName getInstanceNameRef = reinterpret_cast<_GetInstanceName>(0x6731f0);

    return getInstanceNameRef(this, name);
}

void oCItem::setFlag(int flag)
{
/*
    0x2	        Melee Weapon
    0x4	        Ranged Weapon
    0x40000000	Currently equipped
    0x400000	Potion
    0x800	    Ring
*/
    using _SetFlag = void(__thiscall *)(void *pThis, int flag);
    _SetFlag setFlagRef = reinterpret_cast<_SetFlag>(0x672000);

    setFlagRef(this, flag);
}