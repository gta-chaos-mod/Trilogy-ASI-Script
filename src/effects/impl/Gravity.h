// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CCarCtrl.h"

class Gravity : public TimedEffect
{
private:
	float gravity = 0.008f;

public:
	Gravity(float _gravity, int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;
};
