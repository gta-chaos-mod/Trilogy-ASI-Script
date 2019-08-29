// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CCarCtrl.h"

class CustomGravity : public TimedEffect
{
private:
	float gravity = 0.008f;
	int effectRemaining = 1000 * 10;

public:
	CustomGravity(float _gravity, int _duration, std::string _description);

	void Disable() override;

	int GetRemaining() override;

	void HandleTick() override;
};
