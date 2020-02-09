#include "Weather.h"

Weather::Weather (int weatherID) : EffectBase ("effect_weather")
{
    this->weatherID = weatherID;
}

void
Weather::HandleTick ()
{
    EffectBase::HandleTick ();

    CWeather::ForceWeatherNow (weatherID);
}
