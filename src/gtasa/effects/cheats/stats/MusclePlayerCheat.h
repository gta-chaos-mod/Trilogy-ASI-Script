#pragma once

#include "effects/EffectPlaceholder.h"
#include "util/GameUtil.h"

#include "CStats.h"

class MusclePlayerCheat : public EffectPlaceholder
{
public:
	MusclePlayerCheat();

	void Enable() override;
};
