#include "HilarySkinCheat.h"

HilarySkinCheat::HilarySkinCheat () : EffectPlaceholder ("cheat_hilary_skin") {}

void
HilarySkinCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        Call<0x4AE8C0> ("ighlary");
    }
}
