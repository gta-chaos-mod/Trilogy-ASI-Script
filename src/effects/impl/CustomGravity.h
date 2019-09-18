// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CCarCtrl.h"

class CustomGravity : public TimedEffect
{
private:
	float gravity = 0.008f;
	int effectDuration = 1000 * 10;
	int effectRemaining = 1000 * 10;

public:
	CustomGravity(float _gravity, int _duration, const std::string& _description);

	void Disable() override;

	int GetRemaining() override;
	int GetDuration() override;

	TimedEffect* SetRapidFire(bool is_rapid_fire) override;

	void HandleTick() override;
};
