#include "util/EffectBase.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class DrunkPlayerEffect : public EffectBase
{
public:
    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            Command<eScriptCommands::COMMAND_SET_PLAYER_DRUNKENNESS> (0, 0);

            CPad *pad = player->GetPadFromPlayer ();
            if (pad) pad->SetDrunkInputDelay (0);
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            Command<eScriptCommands::COMMAND_SET_PLAYER_DRUNKENNESS> (0, 100);

            CPad *pad = player->GetPadFromPlayer ();
            if (pad) pad->SetDrunkInputDelay (5);
        }
    }
};

DEFINE_EFFECT (DrunkPlayerEffect, "effect_drunk_player", 0);