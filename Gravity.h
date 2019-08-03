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
	Gravity(float _gravity, int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;
};
