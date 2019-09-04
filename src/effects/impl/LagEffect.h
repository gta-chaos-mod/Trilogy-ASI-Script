// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

class LagEffect : public TimedEffect
{
private:
	int wait = 0;
	float* audioSpeed = reinterpret_cast<float*>(0x8CBA6C);

public:
	LagEffect(int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;
};
