#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

class ClearWantedLevelEffect : public OneTimeEffect
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
        CWanted *wanted = FindPlayerWanted (-1);
        if (!wanted) return;

        wanted->CheatWantedLevel (0);
    }
};

DEFINE_EFFECT (ClearWantedLevelEffect, "effect_clear_wanted_level", 0);