#pragma once

#include "util/EffectBase.h"

class LockPlayerInsideVehicleEffect : public EffectBase
{
private:
    bool wasInVehicle = false;

public:
    LockPlayerInsideVehicleEffect ();

    bool CanActivate () override;

    void Enable () override;
    void Disable () override;

    void HandleTick () override;
};
