#include "LanceSkinCheat.h"

LanceSkinCheat::LanceSkinCheat () : EffectPlaceholder ("cheat_lance_skin") {}

void
LanceSkinCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        Call<0x4AE8C0> ("igbuddy");
    }
}
