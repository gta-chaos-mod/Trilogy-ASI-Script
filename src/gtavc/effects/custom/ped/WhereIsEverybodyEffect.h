#pragma once

#include "util/EffectBase.h"

class WhereIsEverybodyEffect : public EffectBase
{
public:
	WhereIsEverybodyEffect();

	void InitializeHooks() override;

	static char __fastcall HookedCPedRender(CPed* thisPed);
};
