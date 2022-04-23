#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <CCheat.h>

class OnePercentSuicideEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (inst->Random (1, 100) == 1) CCheat::SuicideCheat ();

        inst->Disable ();
    }
};

DEFINE_EFFECT (OnePercentSuicideEffect, "effect_one_percent_suicide",
               GROUP_HEALTH);