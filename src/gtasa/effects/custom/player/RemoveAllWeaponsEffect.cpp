#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

class RemoveAllWeaponsEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player) GameUtil::ClearWeapons (player);
    }
};

DEFINE_EFFECT (RemoveAllWeaponsEffect, "effect_remove_all_weapons", 0);