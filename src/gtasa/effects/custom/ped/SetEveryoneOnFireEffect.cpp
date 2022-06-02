#include "effects/OneTimeEffect.h"

#include <CFireManager.h>

class SetEveryoneOnFireEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (CPed *ped : CPools::ms_pPedPool)
        {
            ped->m_nPhysicalFlags.bFireProof = false;

            gFireManager.StartFire (ped, nullptr, 1.0f, 1, 7000, 100);
        }
    }
};

DEFINE_EFFECT (SetEveryoneOnFireEffect, "effect_set_everyone_on_fire", GROUP_HEALTH);