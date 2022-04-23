#include <util/EffectBase.h>

#include <CWeather.h>

class WeatherEffect : public EffectBase
{
    eWeatherType weather = eWeatherType::WEATHER_EXTRASUNNY_LA;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        this->weather
            = (eWeatherType) inst->GetCustomData ().value ("weatherID", 0);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CWeather::ForceWeatherNow (this->weather);
    }
};

DEFINE_EFFECT (WeatherEffect, "effect_weather", GROUP_WEATHER);
