#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

class RemoveEveryonesWeaponsEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (CPed *ped : CPools::ms_pPedPool)
            GameUtil::ClearWeapons (ped);
    }
};

DEFINE_EFFECT (RemoveEveryonesWeaponsEffect, "effect_remove_everyones_weapons",
               0);