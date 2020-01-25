#pragma once

#include "effects/EffectPlaceholder.h"

#include "CCutsceneMgr.h"

class GetWastedEffect : public EffectPlaceholder
{
public:
	GetWastedEffect();

	void Enable() override;
};
