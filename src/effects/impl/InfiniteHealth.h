// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "extra/CPedDamageResponseCalculator.h"

#include "CTaskSimpleCarSetPedOut.h"

class InfiniteHealth : public TimedEffect
{
public:
	static bool onlyPlayer;

public:
	InfiniteHealth(bool _onlyPlayer, int _duration, const std::string& _description);

	void InitializeHooks() override;

	void Disable() override;

	void HandleTick() override;

private:
	static void __fastcall HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, uint8_t* cDamageReponseInfo, char a4);

	static void __fastcall HookedKillPedsInVehicle(CVehicle* thisVehicle);
};
