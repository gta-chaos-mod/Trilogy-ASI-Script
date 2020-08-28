#pragma once

#include "util/EffectBase.h"
#include "util/Teleportation.h"

#include "CCheat.h"

#include "CTaskSimpleCarSetPedOut.h"

class FreefallEffect : public EffectBase
{
private:
    bool isInVehicle = false;

public:
    FreefallEffect ();

    void HandleTick () override;
};
