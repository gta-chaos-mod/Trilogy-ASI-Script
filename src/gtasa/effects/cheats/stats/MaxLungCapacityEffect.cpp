#include "effects/OneTimeEffect.h"

#include <CStats.h>

class MaxLungCapacityEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (STAT_LUNG_CAPACITY, 1000.0f); // Lung capacity
    }
};

DEFINE_EFFECT (MaxLungCapacityEffect, "effect_max_lung_capacity", 0);