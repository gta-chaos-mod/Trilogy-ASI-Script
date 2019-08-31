// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

class LockPlayerInsideVehicle : public TimedEffect
{
public:
	LockPlayerInsideVehicle(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
