#include <util/EffectBase.h>

#include "extensions/ScriptCommands.h"

using namespace plugin;

class CinematicVehicleCameraEffect : public EffectBase
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
        Command<eScriptCommands::COMMAND_SET_PLAYER_IN_CAR_CAMERA_MODE> (5);
    }
};

DEFINE_EFFECT (CinematicVehicleCameraEffect, "effect_cinematic_vehicle_camera",
               GROUP_CAMERA);