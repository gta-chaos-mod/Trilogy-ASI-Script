#include <util/EffectBase.h>

#include "extensions/ScriptCommands.h"

using namespace plugin;

class DrunkPlayerEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            Command<eScriptCommands::COMMAND_SET_PLAYER_DRUNKENNESS> (0, 0);
            player->GetPadFromPlayer ()->SetDrunkInputDelay (0);
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            Command<eScriptCommands::COMMAND_SET_PLAYER_DRUNKENNESS> (0, 100);
            player->GetPadFromPlayer ()->SetDrunkInputDelay (5);
        }
    }
};

DEFINE_EFFECT (DrunkPlayerEffect, "effect_drunk_player", 0);