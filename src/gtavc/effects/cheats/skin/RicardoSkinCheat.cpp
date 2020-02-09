#include "RicardoSkinCheat.h"

RicardoSkinCheat::RicardoSkinCheat () : EffectPlaceholder ("cheat_ricardo_skin")
{
}

void
RicardoSkinCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        Call<0x4AE8C0> ("igdiaz");
    }
}
