#pragma once

#include "effects/EffectPlaceholder.h"
#include "util/GameUtil.h"

#include "CStats.h"

class FatPlayerCheat : public EffectPlaceholder
{
public:
	FatPlayerCheat();

	void Enable() override;
};
