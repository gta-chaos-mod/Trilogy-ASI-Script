#include "DisableAllWeaponDamageEffect.h"

DisableAllWeaponDamageEffect::DisableAllWeaponDamageEffect()
	: EffectBase("effect_disable_all_weapon_damage")
{
	AddType("health");
}

void DisableAllWeaponDamageEffect::InitializeHooks() {
	EffectBase::InitializeHooks();

	for (int address : { 0x5C4089, 0x5C9DBE, 0x5CBC95, 0x5CE361, 0x5CF34B, 0x5CF54A }) {
		HookCall(address, HookedCPedInflictDamage);
	}

	for (int address : { 0x5C433C, 0x5C9EFB, 0x5CBE20, 0x5CE6D8, 0x5CF9EE }) {
		HookCall(address, HookedCVehicleInflictDamage);
	}
}

bool __fastcall DisableAllWeaponDamageEffect::HookedCPedInflictDamage(CPed* thisPed, void* edx, CEntity* source, eWeaponType weapon, float damage, ePedPieceTypes pedPiece, uchar unknown) {
	if (weapon <= eWeaponType::WEAPONTYPE_BRASSKNUCKLE || weapon == eWeaponType::WEAPONTYPE_ANYMELEE) {
		thisPed->InflictDamage(source, weapon, damage, pedPiece, unknown);
		return true;
	}

	return false;
}

bool __fastcall DisableAllWeaponDamageEffect::HookedCVehicleInflictDamage(CVehicle* thisVehicle, void* edx, CEntity* source, eWeaponType weapon, float damage, CVector hitPosition) {
	return false;
}
