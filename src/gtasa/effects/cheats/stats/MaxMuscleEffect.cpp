#include <effects/OneTimeEffect.h>
#include <util/GameUtil.h>

#include "CStats.h"

class MaxMuscleEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (eStats::STAT_MUSCLE, 1000.0f);

        GameUtil::RebuildPlayer ();
    }
};

DEFINE_EFFECT (MaxMuscleEffect, "effect_max_muscle", 0);