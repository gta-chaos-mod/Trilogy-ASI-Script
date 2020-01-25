#pragma once

#include "util/EffectBase.h"

#include "CWorld.h"
#include "extensions/ScriptCommands.h"

class PedsExplodeWhenRunOverEffect : public EffectBase
{
private:
	static bool hasRunOverPed;

public:
	PedsExplodeWhenRunOverEffect();

	void InitializeHooks() override;

private:
	static void __fastcall HookedCPedKillPedWithCar(CPed* thisPed, void* edx, CVehicle* car, float arg1, bool arg2);
	static void HookedCWorldTriggerExplosion(CVector* point, float radius, float visibleDistance, CEntity* victim, CEntity* creator, bool a7, float damage);
};
