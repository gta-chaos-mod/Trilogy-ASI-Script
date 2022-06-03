#include "util/EffectBase.h"
#include "util/GameUtil.h"

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
        CPlayerPed *player = FindPlayerPed ();
        if (!player || !CanActivate ())
        {
            inst->ResetTimer ();
            return;
        }

        CCheat::SuicideCheat ();
        inst->Disable ();
    }
};

// TODO: Maybe remove and instead just have Get Wasted? Same deal anyway.
DEFINE_EFFECT (SuicideEffect, "effect_suicide", GROUP_HEALTH);