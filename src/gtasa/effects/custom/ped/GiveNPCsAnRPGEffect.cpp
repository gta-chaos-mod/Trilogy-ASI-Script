#include "effects/OneTimeEffect.h"

#include <CStreaming.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class GiveNPCsAnRPGEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();

        CStreaming::RequestModel (MODEL_ROCKETLA, 2); // Rocket Launcher
        CStreaming::LoadAllRequestedModels (false);

        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (ped == player) continue;

            Command<eScriptCommands::COMMAND_GIVE_WEAPON_TO_CHAR> (
                ped, WEAPON_RLAUNCHER, 9999);
            Command<eScriptCommands::COMMAND_SET_CURRENT_CHAR_WEAPON> (
                ped, WEAPON_RLAUNCHER);
        }

        CStreaming::SetModelIsDeletable (MODEL_ROCKETLA);
    }
};

DEFINE_EFFECT (GiveNPCsAnRPGEffect, "effect_give_npcs_an_rpg", 0);