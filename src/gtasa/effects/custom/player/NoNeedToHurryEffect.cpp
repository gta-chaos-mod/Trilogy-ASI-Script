#include "util/EffectBase.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class NoNeedToHurryEffect : public EffectBase
{
public:
    void
    OnEnd (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            Command<eScriptCommands::
                        COMMAND_SET_VEHICLE_AIR_RESISTANCE_MULTIPLIER> (vehicle,
                                                                        0.0f);
        }

        CPlayerPed *player = FindPlayerPed ();
        if (player) player->m_pPlayerData->m_bPlayerSprintDisabled = false;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            Command<eScriptCommands::
                        COMMAND_SET_VEHICLE_AIR_RESISTANCE_MULTIPLIER> (vehicle,
                                                                        10.0f);
        }
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            player->m_pPlayerData->m_bPlayerSprintDisabled = true;

            CPad *pad = player->GetPadFromPlayer ();
            if (pad) pad->NewState.m_bPedWalk = true;
        }
    }
};

DEFINE_EFFECT (NoNeedToHurryEffect, "effect_no_need_to_hurry", GROUP_HANDLING);