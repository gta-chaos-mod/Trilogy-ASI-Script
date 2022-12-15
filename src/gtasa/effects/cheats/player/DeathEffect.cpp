#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class DeathEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
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

        Command<eScriptCommands::COMMAND_SET_CHAR_HEALTH> (player, 0);
        inst->Disable ();
    }
};

DEFINE_EFFECT (DeathEffect, "effect_death", GROUP_HEALTH);