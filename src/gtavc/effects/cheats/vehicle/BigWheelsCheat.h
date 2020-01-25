#pragma once

#include "effects/EffectPlaceholder.h"

class BigWheelsCheat : public EffectPlaceholder
{
public:
	BigWheelsCheat();

	void InitializeHooks() override;

	void Enable() override;

private:
	static void HookedCHudSetHelpMessage(int a1, char a2, char a3);
};
