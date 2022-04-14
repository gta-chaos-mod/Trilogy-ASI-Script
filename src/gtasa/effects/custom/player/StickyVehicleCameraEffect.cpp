#include <util/EffectBase.h>

#include "CCamera.h"

#include "extensions/ScriptCommands.h"

using namespace plugin;

class StickyVehicleCameraEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
        {
            // TODO: Disable player camera movement somehow? Always force
            // camera, no matter the mode?
            Command<eScriptCommands::COMMAND_POINT_CAMERA_AT_CAR> (
                vehicle, eCamMode::MODE_BEHINDCAR, 2);
        }
    }
};

DEFINE_EFFECT (StickyVehicleCameraEffect, "effect_sticky_vehicle_camera",
               GROUP_CAMERA);