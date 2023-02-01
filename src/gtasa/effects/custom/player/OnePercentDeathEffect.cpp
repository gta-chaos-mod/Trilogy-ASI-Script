#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class OnePercentDeathEffect : public EffectBase
{
    static inline int timesAttempted = 0;

public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetIsOneTimeEffect ();
        inst->SetDuration (1000 * 5);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        int chance = ++timesAttempted >= 5 ? 10 : 100;

        int random = inst->Random (1, chance);

        if (random == 1)
        {
            timesAttempted = 0;

            Command<eScriptCommands::COMMAND_SET_CHAR_HEALTH> (player, 0);
        }
        else if (timesAttempted >= 5)
        {
            timesAttempted = 0;
        }
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
    }
};

DEFINE_EFFECT (OnePercentDeathEffect, "effect_one_percent_death", GROUP_HEALTH);