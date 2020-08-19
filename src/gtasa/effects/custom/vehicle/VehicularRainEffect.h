#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/RandomHelper.h"

class VehicularRainEffect : public EffectBase
{
private:
    int wait = 0;
    std::map<CVehicle *, int> vehicleList = {};

public:
    VehicularRainEffect ();

    void HandleTick ();
};
