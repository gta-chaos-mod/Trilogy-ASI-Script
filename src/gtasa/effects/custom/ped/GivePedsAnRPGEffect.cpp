#include <effects/OneTimeEffect.h>

#include "extensions/ScriptCommands.h"
#include "CStreaming.h"

using namespace plugin;

// TODO: Refactor effects that apply to NPCs to "GiveNPCsAnRPGEffect" and such
class GivePedsAnRPGEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();

        CStreaming::RequestModel (MODEL_ROCKETLA, 2); // Rocket Launcher
        CStreaming::LoadAllRequestedModels (0);

        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (ped == player)
            {
                continue;
            }

            Command<eScriptCommands::COMMAND_GIVE_WEAPON_TO_CHAR> (
                ped, eWeaponType::WEAPON_RLAUNCHER, 9999);
            Command<eScriptCommands::COMMAND_SET_CURRENT_CHAR_WEAPON> (
                ped, eWeaponType::WEAPON_RLAUNCHER);
        }

        CStreaming::SetModelIsDeletable (MODEL_ROCKETLA);
    }
};

DEFINE_EFFECT (GivePedsAnRPGEffect, "effect_give_peds_an_rpg", 0);