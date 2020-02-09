#include "SetAllPedsOnFireEffect.h"

SetAllPedsOnFireEffect::SetAllPedsOnFireEffect ()
    : EffectPlaceholder ("effect_set_all_peds_on_fire")
{
}

void
SetAllPedsOnFireEffect::Enable ()
{
    EffectPlaceholder::Enable ();

    for (CPed *ped : CPools::ms_pPedPool)
    {
        gFireManager.StartFire (ped, NULL, 1.0f, 100);
    }
}
