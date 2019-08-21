// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

class EverybodyBleedNow : public TimedEffect
{
public:
	EverybodyBleedNow(int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;
};
