#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

class WantedLevelPlusTwoEffect : public OneTimeEffect
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
        if (wanted)
        {
            int targetWanted = std::min (wanted->m_nWantedLevel + 2u, 6u);
            wanted->CheatWantedLevel (targetWanted);
        }
    }
};

DEFINE_EFFECT (WantedLevelPlusTwoEffect, "effect_wanted_level_plus_two", 0);