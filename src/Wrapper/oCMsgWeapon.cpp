#include "oCMsgWeapon.h"


oCMsgWeapon * oCMsgWeapon::CreateoCMsgWeapon(int tWeaponSubType, int param2, int param3) // STATIC
{

    void* raw = ::operator new(0x50); // size of this objekt '0x50'

    using _CTor = oCMsgWeapon*(__thiscall *)(void *pThis, int tWeaponSubType, int param2, int param3);
    _CTor ctor = reinterpret_cast<_CTor>(0x006bf630);
    ctor(raw, tWeaponSubType, param2, param3);

    //return u;
    return reinterpret_cast<oCMsgWeapon*>(raw);
}