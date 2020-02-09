#pragma once

#include "util/EffectBase.h"

#include "effects/EffectPlaceholder.h"
#include "effects/generic/SpawnVehicle.h"
#include "effects/generic/Teleport.h"
#include "effects/generic/Weather.h"

class EffectHandler
{
public:
    static EffectBase *Get (std::string state, std::string function);

private:
    static EffectBase *HandleEffect (std::string name);
    static EffectBase *HandleCheat (std::string name);
};
