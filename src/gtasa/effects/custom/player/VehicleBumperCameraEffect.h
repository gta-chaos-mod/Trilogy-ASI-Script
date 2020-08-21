#pragma once

#include "util/EffectBase.h"

#include "extensions/ScriptCommands.h"

class VehicleBumperCameraEffect : public EffectBase
{
public:
    VehicleBumperCameraEffect ();

    void Disable () override;

    void HandleTick () override;
};
