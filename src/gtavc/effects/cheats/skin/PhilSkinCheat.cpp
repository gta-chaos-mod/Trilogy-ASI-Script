#include "PhilSkinCheat.h"

PhilSkinCheat::PhilSkinCheat () : EffectPlaceholder ("cheat_phil_skin") {}

void
PhilSkinCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        Call<0x4AE8C0> ("igphil");
    }
}
