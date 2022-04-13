#include <util/EffectBase.h>

#include "CClock.h"
#include "CWeather.h"

class StopGameClockEffect : public EffectBase
{
private:
    eWeatherType currentWeather = eWeatherType::WEATHER_EXTRASUNNY_LA;
    int          hours          = 0;
    int          minutes        = 0;
    int          seconds        = 0;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        currentWeather = (eWeatherType) CWeather::NewWeatherType;

        hours   = CClock::ms_nGameClockHours;
        minutes = CClock::ms_nGameClockMinutes;
        seconds = CClock::ms_nGameClockSeconds;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CClock::ms_nGameClockHours   = hours;
        CClock::ms_nGameClockMinutes = minutes;
        CClock::ms_nGameClockSeconds = seconds;

        CWeather::ForceWeatherNow (currentWeather);
    }
};

DEFINE_EFFECT (StopGameClockEffect, "effect_stop_game_clock",
               GROUP_TIME | GROUP_WEATHER);