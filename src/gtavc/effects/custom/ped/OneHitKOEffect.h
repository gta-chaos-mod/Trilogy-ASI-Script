#pragma once

#include "util/EffectBase.h"

class OneHitKOEffect : public EffectBase
{
public:
	OneHitKOEffect();

	void InitializeHooks() override;

	void HandleTick() override;

private:
	static void HookedCFontPrintString(float x, float y, char* text);
};
