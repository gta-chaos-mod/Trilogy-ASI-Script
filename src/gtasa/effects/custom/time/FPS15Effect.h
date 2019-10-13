#pragma once

#include "util/EffectBase.h"

class FPS15Effect : public EffectBase
{
private:
	int oldFramerate = 25;
	int framerate = 15;

	static byte oldFrameTimeWait;

public:
	FPS15Effect();

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
