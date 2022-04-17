#include <util/EffectBase.h>
#include <util/GameUtil.h>
#include <util/GenericUtil.h>

#include "extensions/ScriptCommands.h"

using namespace plugin;

class WalkOffEffect : public EffectBase
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

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                Command<eScriptCommands::COMMAND_TASK_WANDER_STANDARD> (player);
                pad->DisablePlayerControls = true;
            }
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                Command<eScriptCommands::COMMAND_CLEAR_CHAR_TASKS_IMMEDIATELY> (
                    player);
                pad->DisablePlayerControls = false;
            }
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                pad->DisablePlayerControls = true;
            }
        }
    }
};

DEFINE_EFFECT (WalkOffEffect, "effect_walk_off", GROUP_CONTROLS);