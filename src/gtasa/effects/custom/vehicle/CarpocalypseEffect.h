#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/RandomHelper.h"

class CarpocalypseEffect : public EffectBase
{
private:
    int                       wait        = 0;
    std::map<CVehicle *, int> vehicleList = {};

    void  RemoveExplodedVehicles (int step);
    float GetSpawnDistance ();

public:
    CarpocalypseEffect ();

    void HandleTick ();
};
