#include <effects/OneTimeEffect.h>
#include <util/GameUtil.h>

#include "CCheat.h"

class SuicideEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        if (CanKillPlayer ())
        {
            CCheat::SuicideCheat ();
            inst->Disable ();
        }
    }

    bool
    CanKillPlayer ()
    {
        return GameUtil::IsPlayerSafe ();
    }
};

DEFINE_EFFECT (SuicideEffect, "effect_suicide", GROUP_HEALTH);