#include <util/EffectBase.h>
#include <util/GameUtil.h>
#include <util/GenericUtil.h>

#include <extensions/ScriptCommands.h>

using namespace plugin;

class NoTasksAllowedEffect : public EffectBase
{
    int wait = 0;

public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        wait = 0;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            Command<eScriptCommands::COMMAND_CLEAR_CHAR_TASKS_IMMEDIATELY> (
                player);
        }

        wait = 100;
    }
};

DEFINE_EFFECT (NoTasksAllowedEffect, "effect_no_tasks_allowed", 0);