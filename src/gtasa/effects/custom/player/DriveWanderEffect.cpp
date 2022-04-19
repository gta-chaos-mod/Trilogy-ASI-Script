#include <effects/OneTimeEffect.h>

#include "extensions/ScriptCommands.h"

using namespace plugin;

class DriveWanderEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        return FindPlayerPed () != nullptr
               && FindPlayerVehicle (-1, false) != nullptr;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CVehicle *vehicle = FindPlayerVehicle (-1, false);
            if (vehicle)
            {
                Command<eScriptCommands::COMMAND_TASK_CAR_DRIVE_WANDER> (
                    player, vehicle, 20.0f,
                    eCarDrivingStyle::DRIVINGSTYLE_STOP_FOR_CARS);
            }
        }
    }
};

DEFINE_EFFECT (DriveWanderEffect, "effect_drive_wander", 0);
