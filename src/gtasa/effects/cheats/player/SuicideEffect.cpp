#include <util/EffectBase.h>
#include <util/GameUtil.h>

#include <CCheat.h>

class SuicideEffect : public EffectBase
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
        CCheat::SuicideCheat ();
        inst->Disable ();
    }
};

DEFINE_EFFECT (SuicideEffect, "effect_suicide", GROUP_HEALTH);