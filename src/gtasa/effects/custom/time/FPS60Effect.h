#pragma once

#include "util/EffectBase.h"

class FPS60Effect : public EffectBase
{
private:
	int oldFramerate = 25;
	int framerate = 60;

	byte oldFrameTimeWait = 14;

public:
	FPS60Effect();

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
