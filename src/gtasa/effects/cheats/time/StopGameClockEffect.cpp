#include <util/EffectBase.h>

#include "CClock.h"
#include "CWeather.h"

class StopGameClockEffect : public EffectBase
{
    eWeatherType currentWeather = eWeatherType::WEATHER_EXTRASUNNY_LA;
    int          hours          = 0;
    int          minutes        = 0;
    int          seconds        = 0;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        this->currentWeather = (eWeatherType) CWeather::NewWeatherType;

        this->hours   = CClock::ms_nGameClockHours;
        this->minutes = CClock::ms_nGameClockMinutes;
        this->seconds = CClock::ms_nGameClockSeconds;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CClock::ms_nGameClockHours   = this->hours;
        CClock::ms_nGameClockMinutes = this->minutes;
        CClock::ms_nGameClockSeconds = this->seconds;

        CWeather::ForceWeatherNow (this->currentWeather);
    }
};

DEFINE_EFFECT (StopGameClockEffect, "effect_stop_game_clock",
               GROUP_TIME | GROUP_WEATHER);