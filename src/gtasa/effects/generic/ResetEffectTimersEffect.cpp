#include "effects/OneTimeEffect.h"
#include "util/EffectHandler.h"

class ResetEffectTimersEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (auto &effect : EffectHandler::GetActiveEffects ())
        {
            // Reset Effect Timers
            if (effect.IsRunning ()) effect.ResetTimer ();

            // Reinvoke one-time effects
            if (effect.GetEffectDuration () == 0) effect.Start ();
        }
    }
};

DEFINE_EFFECT (ResetEffectTimersEffect, "effect_reset_effect_timers", 0);
