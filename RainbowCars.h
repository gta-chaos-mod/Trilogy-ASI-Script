#pragma once

#include "TimedEffect.h"

class RainbowCars : public TimedEffect
{
private:
	int wait = 0;

public:
	RainbowCars(int _duration, std::string _description);

	void HandleTick() override;
};

