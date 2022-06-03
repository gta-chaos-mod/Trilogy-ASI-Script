#include "effects/OneTimeEffect.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class DriveWanderEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        return FindPlayerPed () && FindPlayerVehicle (-1, false);
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (!vehicle) return;

        Command<eScriptCommands::COMMAND_TASK_CAR_DRIVE_WANDER> (
            player, vehicle, 20.0f,
            eCarDrivingStyle::DRIVINGSTYLE_STOP_FOR_CARS);
    }
};

DEFINE_EFFECT (DriveWanderEffect, "effect_drive_wander", 0);
