#include "CinematicVehicleCameraEffect.h"

CinematicVehicleCameraEffect::CinematicVehicleCameraEffect ()
    : EffectBase ("effect_cinematic_vehicle_camera")
{
    AddType ("camera");
}

bool
CinematicVehicleCameraEffect::CanActivate ()
{
    CVehicle *vehicle = FindPlayerVehicle (-1, false);

    return vehicle != nullptr;
}

void
CinematicVehicleCameraEffect::Disable ()
{
    Command<eScriptCommands::COMMAND_SET_CINEMA_CAMERA> (false);

    EffectBase::Disable ();
}

void
CinematicVehicleCameraEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    CVehicle *vehicle = FindPlayerVehicle (-1, false);
    Command<eScriptCommands::COMMAND_SET_CINEMA_CAMERA> (vehicle != nullptr);
}
