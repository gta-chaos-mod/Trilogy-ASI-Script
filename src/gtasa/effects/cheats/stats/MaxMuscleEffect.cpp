#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStats.h>

class MaxMuscleEffect : public OneTimeEffect
{
public:
    // Will not activate for CC if the player has more than 750/1000 muscle.
    bool
    CanActivate () override
    {
        return CStats::GetStatValue (STAT_MUSCLE) < 750.0f;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (STAT_MUSCLE, 1000.0f);

        GameUtil::RebuildPlayer ();
    }
};

DEFINE_EFFECT (MaxMuscleEffect, "effect_max_muscle", 0);