#include "WeaponCheat1.h"

WeaponCheat1::WeaponCheat1 () : EffectPlaceholder ("cheat_weapons_1") {}

void
WeaponCheat1::InitializeHooks ()
{
    HookCall (0x4AEE14, HookedCHudSetHelpMessage);
}

void
WeaponCheat1::Enable ()
{
    EffectPlaceholder::Enable ();

    Call<0x4AEE00> ();
}

void
WeaponCheat1::HookedCHudSetHelpMessage (int a1, char a2, char a3)
{
}
