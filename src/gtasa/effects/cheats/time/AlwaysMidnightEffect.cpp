#include "util/EffectBase.h"

#include <CClock.h>
#include <CWeather.h>

class AlwaysMidnightEffect : public EffectBase
{
    eWeatherType currentWeather = WEATHER_EXTRASUNNY_LA;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        this->currentWeather
            = (eWeatherType) std::min (CWeather::NewWeatherType,
                                       (short) WEATHER_EXTRACOLOURS_2);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CClock::ms_nGameClockHours   = 0;
        CClock::ms_nGameClockMinutes = 0;
        CClock::ms_nGameClockSeconds = 0;

        CWeather::ForceWeatherNow (this->currentWeather);
    }
};

DEFINE_EFFECT (AlwaysMidnightEffect, "effect_always_midnight",
               GROUP_TIME | GROUP_WEATHER);