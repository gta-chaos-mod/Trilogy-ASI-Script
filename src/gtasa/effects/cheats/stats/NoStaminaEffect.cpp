#include "effects/OneTimeEffect.h"

#include <CStats.h>

class NoStaminaEffect : public OneTimeEffect
{
public:
    // Will not activate for CC if the player has less than 250/1000 stamina.
    bool
    CanActivate () override
    {
        return CStats::GetStatValue (STAT_STAMINA) > 250.0f;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (STAT_STAMINA, 0.0f); // Stamina
    }
};

DEFINE_EFFECT (NoStaminaEffect, "effect_no_stamina", 0);