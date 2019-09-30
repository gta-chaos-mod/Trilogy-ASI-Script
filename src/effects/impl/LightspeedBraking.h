// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "effects/other/Vehicle.h"

#include "CCarCtrl.h"

class LightspeedBraking : public TimedEffect
{
private:
	tHandlingData origVehicleHandling[210];

public:
	LightspeedBraking(int _duration, const std::string& _description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
