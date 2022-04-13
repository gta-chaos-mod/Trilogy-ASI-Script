#include <effects/OneTimeEffect.h>

#include "CStats.h"

class MaxStaminaEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (eStats::STAT_STAMINA, 1000.0f); // Stamina
    }
};

DEFINE_EFFECT (MaxStaminaEffect, "effect_max_stamina", 0);