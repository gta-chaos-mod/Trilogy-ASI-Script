#pragma once

#include "util/EffectBase.h"

#include "extensions/ScriptCommands.h"

class ThermalVisionEffect : public EffectBase
{
public:
	ThermalVisionEffect();

	void Disable() override;

	void HandleTick() override;
};
