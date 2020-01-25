#pragma once

#include "util/EffectBase.h"

#include "CStreaming.h"

#include "extensions/ScriptCommands.h"

class RingRingEffect : public EffectBase
{
private:
	int wait = 0;

public:
	RingRingEffect();

	bool CanActivate() override;

	void Disable() override;

	void HandleTick() override;
};
