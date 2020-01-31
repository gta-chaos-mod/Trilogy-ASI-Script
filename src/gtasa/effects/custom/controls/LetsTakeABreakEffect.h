#pragma once

#include "util/EffectBase.h"

#include "extensions/ScriptCommands.h"

class LetsTakeABreakEffect : public EffectBase
{
public:
	LetsTakeABreakEffect();

	void Disable() override;

	void HandleTick() override;
};
