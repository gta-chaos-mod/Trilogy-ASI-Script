#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/RandomHelper.h"

#include "cHandlingDataMgr.h"

class UnflippableVehiclesEffect : public EffectBase
{
private:
    tHandlingData origVehicleHandling[210] = {};

public:
    UnflippableVehiclesEffect ();

    void Enable () override;
    void Disable () override;

    void HandleTick () override;
};
