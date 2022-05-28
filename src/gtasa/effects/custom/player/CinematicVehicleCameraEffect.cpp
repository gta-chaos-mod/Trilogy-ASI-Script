#include "util/EffectBase.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class CinematicVehicleCameraEffect : public EffectBase
{
public:
    void
    OnEnd (EffectInstance *inst) override
    {
        Command<eScriptCommands::COMMAND_SET_CINEMA_CAMERA> (false);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        Command<eScriptCommands::COMMAND_SET_CINEMA_CAMERA> (true);
    }
};

DEFINE_EFFECT (CinematicVehicleCameraEffect, "effect_cinematic_vehicle_camera",
               GROUP_CAMERA);