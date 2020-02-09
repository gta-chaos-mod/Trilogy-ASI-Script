#pragma once

#include "util/EffectBase.h"

#include "CWeather.h"

class Weather : public EffectBase
{
private:
    int weatherID = 0;

public:
    Weather (int id);

    void HandleTick () override;
};
