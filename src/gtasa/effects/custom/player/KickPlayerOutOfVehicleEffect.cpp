#include "effects/OneTimeEffect.h"

#include <CTheScripts.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class KickPlayerOutOfVehicleEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        return FindPlayerVehicle (-1, false);
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
            if (playerVehicle)
            {
                Command<eScriptCommands::COMMAND_TASK_LEAVE_CAR_IMMEDIATELY> (
                    player, playerVehicle);
                if (!CTheScripts::IsPlayerOnAMission ())
                {
                    playerVehicle->m_nVehicleFlags.bConsideredByPlayer = false;
                }
            }
        }
    }
};

DEFINE_EFFECT (KickPlayerOutOfVehicleEffect,
               "effect_kick_player_out_of_vehicle", 0);