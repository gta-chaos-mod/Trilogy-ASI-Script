#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

class WantedLevelSixStarsEffect : public OneTimeEffect
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
        if (wanted) wanted->CheatWantedLevel (6);
    }
};

DEFINE_EFFECT (WantedLevelSixStarsEffect, "effect_wanted_level_six_stars", 0);