#include "FullArmorCheat.h"

FullArmorCheat::FullArmorCheat () : EffectPlaceholder ("cheat_full_armor") {}

void
FullArmorCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CPlayerPed *ped = FindPlayerPed ();
    if (ped && ped->GetPlayerInfoForThisPlayerPed ())
    {
        ped->m_fArmour = ped->GetPlayerInfoForThisPlayerPed ()->m_nMaxArmour;
    }
}
