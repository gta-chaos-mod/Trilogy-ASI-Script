#include <effects/OneTimeEffect.h>

#include "CStats.h"

class NoStaminaEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (eStats::STAT_STAMINA, 0.0f); // Stamina
    }
};

DEFINE_EFFECT (NoStaminaEffect, "effect_no_stamina", 0);