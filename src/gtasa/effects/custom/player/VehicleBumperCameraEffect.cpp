#include "VehicleBumperCameraEffect.h"

VehicleBumperCameraEffect::VehicleBumperCameraEffect ()
    : EffectBase ("effect_vehicle_bumper_camera")
{
    AddType ("camera");
}

void
VehicleBumperCameraEffect::Disable ()
{
    Command<eScriptCommands::COMMAND_SET_PLAYER_IN_CAR_CAMERA_MODE> (2);

    EffectBase::Disable ();
}

void
VehicleBumperCameraEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    Command<eScriptCommands::COMMAND_SET_PLAYER_IN_CAR_CAMERA_MODE> (0);
}
