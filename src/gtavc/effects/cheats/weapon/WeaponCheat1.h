#pragma once

#include "effects/EffectPlaceholder.h"

class WeaponCheat1 : public EffectPlaceholder
{
public:
	WeaponCheat1();

	void InitializeHooks() override;

	void Enable() override;

private:
	static void HookedCHudSetHelpMessage(int a1, char a2, char a3);
};
