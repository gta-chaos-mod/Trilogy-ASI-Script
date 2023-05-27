#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

struct ClearWantedLevel
{
};

class WantedLevelEffect : public OneTimeEffect
{
private:
    int level = 0;

public:
    WantedLevelEffect (int addStars) : level (addStars) {}
    WantedLevelEffect (ClearWantedLevel clearLevel) : level (-6) {}

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

        int targetWanted
            = std::clamp (int (wanted->m_nWantedLevel) + level, 0, 6);
        wanted->CheatWantedLevel (targetWanted);
    }
};

DEFINE_EFFECT (WantedLevelEffect, "effect_wanted_level_plus_two", GROUP_WANTED,
               2);
DEFINE_EFFECT (WantedLevelEffect, "effect_wanted_level_six_stars", GROUP_WANTED,
               6);
DEFINE_EFFECT (WantedLevelEffect, "effect_clear_wanted_level", GROUP_WANTED,
               ClearWantedLevel{});