#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class GetJetpackEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return false;

        if (FindPlayerVehicle (-1, false)) return false;

        if (Command<eScriptCommands::COMMAND_IS_PLAYER_USING_JETPACK> (0))
            return false;

        return GameUtil::IsPlayerSafe ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetTimerVisible (false);
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

        Command<eScriptCommands::COMMAND_TASK_JETPACK> (player);
        inst->Disable ();
    }
};

DEFINE_EFFECT (GetJetpackEffect, "effect_get_jetpack", 0);