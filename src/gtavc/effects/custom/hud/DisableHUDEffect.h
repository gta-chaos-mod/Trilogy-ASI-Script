#pragma once

#include "util/EffectBase.h"

#include "CHud.h"

class DisableHUDEffect : public EffectBase
{
public:
	DisableHUDEffect();

	void InitializeHooks() override;

private:
	static void HookedHUDDraw();
};
