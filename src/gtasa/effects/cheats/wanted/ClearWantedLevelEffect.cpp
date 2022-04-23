#include "CWanted.h"
#include "effects/OneTimeEffect.h"

class ClearWantedLevelEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CWanted *wanted = FindPlayerWanted (-1);
        if (wanted) { wanted->CheatWantedLevel (0); }
    }
};

DEFINE_EFFECT (ClearWantedLevelEffect, "effect_clear_wanted_level", 0);