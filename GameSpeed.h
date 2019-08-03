#pragma once

#include "common.h"
#include "plugin.h"

#include "TimedEffect.h"

class GameSpeed : public TimedEffect
{
private:
	float gameSpeed = 1.0f;

public:
	GameSpeed(float _gameSpeed, int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;
};
