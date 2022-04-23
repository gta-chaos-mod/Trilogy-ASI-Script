#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <algorithm>
#include <experimental/forward_list>

#include <CCheat.h>
#include <extensions/ScriptCommands.h>

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