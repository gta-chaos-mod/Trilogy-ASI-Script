#include "effects/OneTimeEffect.h"

#include <CStats.h>

class NoLungCapacityEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (STAT_LUNG_CAPACITY, 0.0f); // Lung capacity
    }
};

DEFINE_EFFECT (NoLungCapacityEffect, "effect_no_lung_capacity", 0);