#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class OnePercentDeathEffect : public EffectBase
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
        inst->SetIsOneTimeEffect ();
        inst->SetDuration (1000 * 5);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        if (inst->Random (1, 100) == 50)
            Command<eScriptCommands::COMMAND_SET_CHAR_HEALTH> (player, 0);
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