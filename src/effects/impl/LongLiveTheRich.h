// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"
#include "util/DrawHelper.h"

#include "CPickup.h"
#include "extra/CPedDamageResponseCalculator.h"
#include "CPlayerInfo.h"

class LongLiveTheRich : public TimedEffect
{
public:
	static bool isEnabled;
	static int storedMoney;
	static float gainedMoney;

	bool* neverHungryCheat = reinterpret_cast<bool*>(0x969174);

public:
	LongLiveTheRich(int _duration, std::string _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

private:
	static void __fastcall HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, uint8_t* cDamageResponseInfo, char a4);
	static bool __fastcall HookedPickupUpdate(CPickup* thisPickup, void* edx, CPlayerPed* ped, CVehicle* vehicle, int playerId);
};
