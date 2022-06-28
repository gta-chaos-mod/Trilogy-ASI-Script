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
    OnStart (EffectInstance *inst) override
    {
        inst->SetDuration (1000 * 5);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        if (inst->Random (1, 100) == 50) CCheat::SuicideCheat ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player || !CanActivate ())
        {
            inst->ResetTimer ();
            return;
        }
    }
};

DEFINE_EFFECT (OnePercentSuicideEffect, "effect_one_percent_suicide",
               GROUP_HEALTH);