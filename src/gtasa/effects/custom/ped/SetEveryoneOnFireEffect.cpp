#include "SetEveryoneOnFireEffect.h"

SetEveryoneOnFireEffect::SetEveryoneOnFireEffect ()
    : EffectPlaceholder ("effect_set_everyone_on_fire")
{
}

void
SetEveryoneOnFireEffect::Enable ()
{
    EffectPlaceholder::Enable ();

    for (CPed *ped : CPools::ms_pPedPool)
    {
        ped->m_nPhysicalFlags.bFireProof = false;

        gFireManager.StartFire (ped, NULL, 1.0f, 1, 7000, 100);
    }
}
