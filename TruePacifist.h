#pragma once

#include "TimedEffect.h"

#include "CPedDamageResponseCalculator.h"

class TruePacifist : public TimedEffect
{
public:
	TruePacifist(int _duration, std::string _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	static void __fastcall HookedAccountForPedArmour(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, int cDamageResponseInfo);
	static void __fastcall HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, float* a3, char a4);
};

