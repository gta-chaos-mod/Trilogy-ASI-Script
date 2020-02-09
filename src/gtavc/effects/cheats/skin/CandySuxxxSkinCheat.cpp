#include "CandySuxxxSkinCheat.h"

CandySuxxxSkinCheat::CandySuxxxSkinCheat ()
    : EffectPlaceholder ("cheat_candy_suxxx_skin")
{
}

void
CandySuxxxSkinCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        Call<0x4AE8C0> ("igcandy");
    }
}
