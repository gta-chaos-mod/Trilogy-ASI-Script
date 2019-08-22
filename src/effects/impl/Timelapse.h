// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CClock.h"

class Timelapse : public TimedEffect
{
public:
	Timelapse(int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;
};
