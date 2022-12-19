#include "effects/OneTimeEffect.h"

#include <CStats.h>

class MaxStaminaEffect : public OneTimeEffect
{
public:
    // Will not activate for CC if the player has more than 750/1000 stamina.
    bool
    CanActivate () override
    {
        return CStats::GetStatValue (STAT_STAMINA) < 750.0f;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (STAT_STAMINA, 1000.0f); // Stamina
    }
};

DEFINE_EFFECT (MaxStaminaEffect, "effect_max_stamina", 0);