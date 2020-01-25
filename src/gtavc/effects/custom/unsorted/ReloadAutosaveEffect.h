#pragma once

#include "effects/EffectPlaceholder.h"
#include "util/GameUtil.h"

class ReloadAutosaveEffect : public EffectPlaceholder
{
public:
	ReloadAutosaveEffect();

	void Enable() override;
};
