#include <effects/OneTimeEffect.h>

#include <util/GameUtil.h>

class RemoveAllWeaponsEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (CPed *ped : CPools::ms_pPedPool)
        {
            GameUtil::ClearWeaponsExceptParachute (ped);
        }
    }
};

DEFINE_EFFECT (RemoveAllWeaponsEffect, "effect_remove_all_weapons",
               GROUP_HEALTH);