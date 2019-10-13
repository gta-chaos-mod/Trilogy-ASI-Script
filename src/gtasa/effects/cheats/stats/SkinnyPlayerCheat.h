#pragma once

#include "effects/EffectPlaceholder.h"
#include "util/GameUtil.h"

#include "CStats.h"

class SkinnyPlayerCheat : public EffectPlaceholder
{
public:
	SkinnyPlayerCheat();

	void Enable() override;
};
