#pragma once

#include "util/EffectBase.h"

class CPed;

class BobbleHeadsEffect : public EffectBase
{
public:
	BobbleHeadsEffect();

	void Enable() override;

	void Disable() override;

	static void RenderPedEvent(CPed* ped);
};
