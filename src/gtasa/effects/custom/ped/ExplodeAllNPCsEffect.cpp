#include "effects/OneTimeEffect.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class ExplodeAllNPCsEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();

        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (ped == player) continue;

            auto pos = ped->GetPosition ();
            Command<eScriptCommands::COMMAND_ADD_EXPLOSION> (pos.x, pos.y,
                                                             pos.z, 11);
        }
    }
};

DEFINE_EFFECT (ExplodeAllNPCsEffect, "effect_explode_all_npcs", 0);