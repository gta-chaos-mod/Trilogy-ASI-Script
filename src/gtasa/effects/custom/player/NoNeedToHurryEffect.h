#pragma once

#include "util/EffectBase.h"

#include "extensions/ScriptCommands.h"

class NoNeedToHurryEffect : public EffectBase
{
public:
	NoNeedToHurryEffect();

	void Disable() override;

	void HandleTick() override;
};
