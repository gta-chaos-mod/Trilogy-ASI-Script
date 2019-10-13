#pragma once

#include "effects/TimedAddressEffect.h"

#include "CClock.h"

class StopGameClockCheat : public TimedAddressEffect
{
private:
	int hours = 0;
	int minutes = 0;
	int seconds = 0;

public:
	StopGameClockCheat();

	void Enable() override;

	void HandleTick() override;
};
