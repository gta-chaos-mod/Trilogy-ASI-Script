#pragma once

#include "util/EffectBase.h"

class DisableRadarBlipsEffect : public EffectBase
{
public:
	DisableRadarBlipsEffect();

	void InitializeHooks() override;

private:
	static void HookedBlipsDraw();
};
