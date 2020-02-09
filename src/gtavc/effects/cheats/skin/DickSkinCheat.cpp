#include "DickSkinCheat.h"

DickSkinCheat::DickSkinCheat () : EffectPlaceholder ("cheat_dick_skin") {}

void
DickSkinCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        Call<0x4AE8C0> ("igdick");
    }
}
