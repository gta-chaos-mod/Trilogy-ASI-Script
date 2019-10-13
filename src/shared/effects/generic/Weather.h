#pragma once

#include "effects/EffectPlaceholder.h"

#include "CWeather.h"

class Weather : public EffectPlaceholder
{
private:
	int weatherID = 0;

public:
	Weather(int id);

	void Enable() override;
};
