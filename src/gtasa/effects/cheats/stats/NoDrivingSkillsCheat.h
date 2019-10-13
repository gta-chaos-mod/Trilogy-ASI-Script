#pragma once

#include "effects/EffectPlaceholder.h"

#include "CStats.h"

class NoDrivingSkillsCheat : public EffectPlaceholder
{
public:
	NoDrivingSkillsCheat();

	void Enable() override;
};
