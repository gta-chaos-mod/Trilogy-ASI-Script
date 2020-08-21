#include "CinematicVehicleCameraEffect.h"

CinematicVehicleCameraEffect::CinematicVehicleCameraEffect ()
    : EffectBase ("effect_cinematic_vehicle_camera")
{
    AddType ("camera");
}

void
CinematicVehicleCameraEffect::Disable ()
{
    Command<eScriptCommands::COMMAND_SET_PLAYER_IN_CAR_CAMERA_MODE> (2);

    EffectBase::Disable ();
}

void
CinematicVehicleCameraEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    Command<eScriptCommands::COMMAND_SET_PLAYER_IN_CAR_CAMERA_MODE> (5);
}
