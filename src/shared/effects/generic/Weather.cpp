#include "Weather.h"

Weather::Weather(int weatherID)
	: EffectPlaceholder("weather")
{
	this->weatherID = weatherID;
}

void Weather::Enable() {
	EffectPlaceholder::Enable();

	CWeather::ForceWeatherNow(weatherID);
}
