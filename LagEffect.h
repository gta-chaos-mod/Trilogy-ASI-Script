#pragma once

#include "TimedEffect.h"

class LagEffect : public TimedEffect
{
private:
	int wait = 0;

public:
	LagEffect(int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;
};
