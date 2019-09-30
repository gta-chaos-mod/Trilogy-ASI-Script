// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

class DVDScreensaver : public TimedEffect
{
private:
	static bool goingDown;
	static bool goingRight;

	static float x;
	static float y;

public:
	DVDScreensaver(int _duration, const std::string& _description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	static std::pair<float, float> CalculateStartingXY(int boxNumber);
	static std::pair<float, float> CalculateWidthHeight(int boxNumber);
	static void DrawScreensaver();
};
