#include "util/EffectBase.h"

struct CurrentWantedLevel
{
};

class AlwaysWantedEffect : public EffectBase
{
private:
    bool         useCurrentWantedLevel = false;
    unsigned int level                 = 4;

public:
    AlwaysWantedEffect (unsigned int wantedLevel) : level (wantedLevel) {}
    AlwaysWantedEffect (CurrentWantedLevel currentLevel)
        : useCurrentWantedLevel (true)
    {
    }

    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        if (!useCurrentWantedLevel) return;

        CWanted *wanted = FindPlayerWanted (-1);
        if (wanted)
        {
            level = wanted->m_nWantedLevel;
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        player->CheatWantedLevel (level);
    }
};

DEFINE_EFFECT (AlwaysWantedEffect, "effect_always_wanted", GROUP_WANTED, 4);
DEFINE_EFFECT (AlwaysWantedEffect, "effect_freeze_wanted_level", GROUP_WANTED,
               CurrentWantedLevel{});