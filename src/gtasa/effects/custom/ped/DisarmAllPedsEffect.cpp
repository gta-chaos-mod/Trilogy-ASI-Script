#include <effects/OneTimeEffect.h>

#include "extensions/ScriptCommands.h"
#include "CStreaming.h"

using namespace plugin;

class DisarmAllPedsEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (ped == player)
            {
                continue;
            }

            Command<eScriptCommands::COMMAND_REMOVE_ALL_CHAR_WEAPONS> (ped);
        }
    }
};

DEFINE_EFFECT (DisarmAllPedsEffect, "effect_disarm_all_peds", 0);