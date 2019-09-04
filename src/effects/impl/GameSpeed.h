// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CCarCtrl.h"

class GameSpeed : public TimedEffect
{
private:
	float gameSpeed = 1.0f;
	float* audioSpeed = reinterpret_cast<float*>(0x8CBA6C);

public:
	GameSpeed(float _gameSpeed, int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;
};
