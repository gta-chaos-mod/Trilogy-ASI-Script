// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "effects/other/Vehicle.h"

#include "CCarCtrl.h"

class Suspension : public TimedEffect
{
private:
	tHandlingData origVehicleHandling[210];
	float suspension = 1.0f;

public:
	Suspension(float _suspension, int _duration, const std::string& _description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
