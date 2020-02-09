#include "WeaponCheat1.h"

WeaponCheat1::WeaponCheat1 () : EffectPlaceholder ("cheat_weapons_1")
{
    AddType ("weapons");
}

void
WeaponCheat1::Enable ()
{
    EffectPlaceholder::Enable ();

    CCheat::WeaponCheat1 ();
}
