#include "effects/OneTimeEffect.h"
#include "util/Globals.h"

#include <CTheScripts.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class KickPlayerOutOfVehicleEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        return FindPlayerVehicle (-1, false)
               && !Globals::enabledEffects["lock_player_inside_vehicle"];
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (!vehicle) return;

        Command<eScriptCommands::COMMAND_TASK_LEAVE_CAR_IMMEDIATELY> (player,
                                                                      vehicle);
        if (CTheScripts::IsPlayerOnAMission ()) return;

        vehicle->m_nVehicleFlags.bConsideredByPlayer = false;
    }
};

DEFINE_EFFECT (KickPlayerOutOfVehicleEffect,
               "effect_kick_player_out_of_vehicle", 0);