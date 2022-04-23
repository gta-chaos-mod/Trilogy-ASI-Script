#include <util/EffectBase.h>

#include <extensions/ScriptCommands.h>

using namespace plugin;

class VehicleBumperCameraEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Command<eScriptCommands::COMMAND_SET_PLAYER_IN_CAR_CAMERA_MODE> (2);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        Command<eScriptCommands::COMMAND_SET_PLAYER_IN_CAR_CAMERA_MODE> (0);
    }
};

DEFINE_EFFECT (VehicleBumperCameraEffect, "effect_vehicle_bumper_camera",
               GROUP_CAMERA);