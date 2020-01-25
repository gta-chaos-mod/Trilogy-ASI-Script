#pragma once

#include "util/EffectBase.h"

#include "CCamera.h"
#include "CDraw.h"

#include "extensions/ScriptCommands.h"

class QuakeFOVEffect : public EffectBase
{
private:
	float* CDraw_pfScreenFieldOfView = (float*)0x8D5038;

public:
	QuakeFOVEffect();

	void Enable() override;

	void HandleTick() override;
};
