#include "SonnySkinCheat.h"

SonnySkinCheat::SonnySkinCheat () : EffectPlaceholder ("cheat_sonny_skin") {}

void
SonnySkinCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        Call<0x4AE8C0> ("igsonny");
    }
}
