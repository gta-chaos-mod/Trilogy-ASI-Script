// Copyright (c) 2019 Lordmau5
#pragma once

#include "TimedEffect.h"

#include "CPickup.h"
#include "CPedDamageResponseCalculator.h"
#include "CPlayerInfo.h"

class LongLiveTheRich : public TimedEffect
{
public:
	static bool isEnabled;

private:
	int storedMoney = 0;

public:
	LongLiveTheRich(int _duration, std::string _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

private:
	static void __fastcall HookedAccountForPedArmour(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, int cDamageResponseInfo);
	static void __fastcall HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, float* a3, char a4);
	static bool __fastcall HookedPickupUpdate(CPickup* thisPickup, void* edx, CPlayerPed* ped, CVehicle* vehicle, int playerId);
};
