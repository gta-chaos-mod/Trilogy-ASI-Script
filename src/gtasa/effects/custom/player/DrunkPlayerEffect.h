#pragma once

#include "util/EffectBase.h"

#include "extensions/ScriptCommands.h"

class DrunkPlayerEffect : public EffectBase
{
public:
	DrunkPlayerEffect();

	void Disable() override;

	void HandleTick() override;
};
