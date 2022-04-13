#include <effects/OneTimeEffect.h>

#include "CWanted.h"

class WantedLevelPlusTwoEffect : public OneTimeEffect
{
public:
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