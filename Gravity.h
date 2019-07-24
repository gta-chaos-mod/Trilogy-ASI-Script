#pragma once

#include "common.h"
#include "plugin.h"

#include "CCarCtrl.h"

#include "TimedEffect.h"

class Gravity : public TimedEffect
{
private:
	float gravity = 0.008f;

public:
	Gravity(float _gravity, int duration, std::string description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
