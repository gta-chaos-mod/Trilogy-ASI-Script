#pragma once

#include "TimedEffect.h"

#include <random>

class LagEffect : public TimedEffect
{
private:
	bool slow = false;
	int wait = 0;

public:
	LagEffect(int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;
};

