#include "WeaponCheat2.h"

WeaponCheat2::WeaponCheat2 () : EffectPlaceholder ("cheat_weapons_2") {}

void
WeaponCheat2::InitializeHooks ()
{
    HookCall (0x4AEC84, HookedCHudSetHelpMessage);
}

void
WeaponCheat2::Enable ()
{
    EffectPlaceholder::Enable ();

    Call<0x4AEC70> ();
}

void
WeaponCheat2::HookedCHudSetHelpMessage (int a1, char a2, char a3)
{
}
