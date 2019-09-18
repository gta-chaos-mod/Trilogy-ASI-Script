// Copyright (c) 2019 Lordmau5
#include "TruePacifist.h"

bool TruePacifist::isEnabled = false;

TruePacifist::TruePacifist(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "health") {}

void TruePacifist::InitializeHooks() {
	patch::RedirectCall(0x4B5B19, HookedAccountForPedArmour);
	patch::RedirectCall(0x4B5B27, HookedComputeWillKillPed);

	for (int address : { 0x73647F, 0x73B0BF, 0x73BEDD }) {
		patch::RedirectCall(address, HookedVehicleInflictDamage);
	}
}

void TruePacifist::Enable() {
	isEnabled = true;
}

void TruePacifist::Disable() {
	isEnabled = false;

	TimedEffect::Disable();
}

void __fastcall TruePacifist::HookedAccountForPedArmour(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, uint8_t* cDamageResponseInfo) {
	if (isEnabled) {
		return;
	}

	thisCalc->AccountForPedArmour(ped, cDamageResponseInfo);
}

void __fastcall TruePacifist::HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, uint8_t* cDamageReponseInfo, char a4) {
	if (thisCalc->m_weaponType <= eWeaponType::WEAPON_BRASSKNUCKLE || thisCalc->m_weaponType == eWeaponType::WEAPON_PARACHUTE) {
		thisCalc->ComputeWillKillPed(ped, cDamageReponseInfo, a4);
		return;
	}

	if (isEnabled && thisCalc->m_pDamager && thisCalc->m_pDamager->m_nType == eEntityType::ENTITY_TYPE_PED) {
		return;
	}

	thisCalc->ComputeWillKillPed(ped, cDamageReponseInfo, a4);
}

void TruePacifist::HookedVehicleInflictDamage(CVehicle* thisVehicle, void* edx, CPed* who, eWeaponType type, float damage, CVector coords) {
	if (isEnabled) {
		return;
	}

	CallMethod<0x6D7C90, CVehicle*>(thisVehicle, who, type, damage, coords);
}
