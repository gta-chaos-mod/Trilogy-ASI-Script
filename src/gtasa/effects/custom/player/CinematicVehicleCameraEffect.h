#pragma once

#include "util/EffectBase.h"

#include "extensions/ScriptCommands.h"

class CinematicVehicleCameraEffect : public EffectBase
{
public:
    CinematicVehicleCameraEffect ();

    bool CanActivate () override;

    void Disable () override;

    void HandleTick () override;
};
