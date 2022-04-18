#include <effects/OneTimeEffect.h>
#include <util/EffectHandler.h>

class ClearActiveEffectsEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (auto &effect : EffectHandler::GetActiveEffects ())
        {
            effect.Disable ();
        }
    }
};

DEFINE_EFFECT (ClearActiveEffectsEffect, "effect_clear_active_effects", 0);
