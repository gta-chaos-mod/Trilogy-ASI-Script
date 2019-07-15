#pragma once

#include "TimedEffect.h"

#include "Vehicle.h"
#include "CCarCtrl.h"

class Suspension : public TimedEffect
{
private:
	float suspension = 1.0f;

public:
	Suspension(float _suspension, int _duration, std::string _description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
