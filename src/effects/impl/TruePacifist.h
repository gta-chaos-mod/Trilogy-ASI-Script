// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "extra/CPedDamageResponseCalculator.h"

class TruePacifist : public TimedEffect
{
public:
	static bool isEnabled;

public:
	TruePacifist(int _duration, const std::string& _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

private:
	static void __fastcall HookedAccountForPedArmour(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, uint8_t* cDamageReponseInfo);
	static void __fastcall HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, uint8_t* cDamageReponseInfo, char a4);
	static void __fastcall HookedVehicleInflictDamage(CVehicle* thisVehicle, void* edx, CPed* who, eWeaponType type, float damage, CVector coords);
};
