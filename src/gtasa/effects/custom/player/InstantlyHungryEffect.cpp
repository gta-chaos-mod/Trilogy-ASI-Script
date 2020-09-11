#include "InstantlyHungryEffect.h"

InstantlyHungryEffect::InstantlyHungryEffect ()
    : EffectPlaceholder ("effect_instantly_hungry")
{
}

void
InstantlyHungryEffect::Enable ()
{
    EffectPlaceholder::Enable ();

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        player->GetPlayerInfoForThisPlayerPed ()->m_nNumHoursDidntEat = 60;
        CallMethod<0x56E610, CPlayerInfo *> (
            player->GetPlayerInfoForThisPlayerPed ());
        injector::WriteMemory (0xB9B8F0, true); // bHungryMessageShown
    }
}
