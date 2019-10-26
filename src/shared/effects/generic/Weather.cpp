#include "Weather.h"

Weather::Weather(int weatherID)
	: EffectPlaceholder("effect_weather")
{
	this->weatherID = weatherID;
}

void Weather::Enable() {
	EffectPlaceholder::Enable();

	CWeather::ForceWeatherNow(weatherID);
}
