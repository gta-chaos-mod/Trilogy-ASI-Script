#include <util/EffectBase.h>

#include "CClock.h"
#include "CWeather.h"

class AlwaysMidnightEffect : public EffectBase
{
private:
    eWeatherType currentWeather = eWeatherType::WEATHER_EXTRASUNNY_LA;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        currentWeather = (eWeatherType) CWeather::NewWeatherType;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CClock::ms_nGameClockHours   = 0;
        CClock::ms_nGameClockMinutes = 0;
        CClock::ms_nGameClockSeconds = 0;

        CWeather::ForceWeatherNow (currentWeather);
    }
};

DEFINE_EFFECT (AlwaysMidnightEffect, "effect_always_midnight",
               GROUP_TIME | GROUP_WEATHER);