#include "PedsExplodeWhenRunOverEffect.h"

bool PedsExplodeWhenRunOverEffect::hasRunOverPed = false;

PedsExplodeWhenRunOverEffect::PedsExplodeWhenRunOverEffect()
	: EffectBase("effect_peds_explode_when_run_over") {}

void PedsExplodeWhenRunOverEffect::InitializeHooks() {
	for (int address : { 0x54C5CC, 0x54C642, 0x60461F, 0x60491B, 0x604A0D }) {
		HookCall(address, HookedCPedKillPedWithCar);
	}

	HookCall(0x7374DA, HookedCWorldTriggerExplosion);
	HookCall(0x568271, HookedDamageAffectsPed);
}

void __fastcall PedsExplodeWhenRunOverEffect::HookedCPedKillPedWithCar(CPed* thisPed, void* edx, CVehicle* car, float arg1, bool arg2) {
	hasRunOverPed = true;

	CVector pos = thisPed->GetPosition();
	Command<eScriptCommands::COMMAND_ADD_EXPLOSION>(pos.x, pos.y, pos.z, 7);

	thisPed->KillPedWithCar(car, arg1, arg2);
}

void PedsExplodeWhenRunOverEffect::HookedCWorldTriggerExplosion(CVector* point, float radius, float visibleDistance, CEntity* victim, CEntity* creator, bool a7, float damage) {
	if (hasRunOverPed) {
		damage = 0.0f;
	}

	CWorld::TriggerExplosion(*point, radius, visibleDistance, victim, creator, a7, damage);

	hasRunOverPed = false;
}

bool __fastcall PedsExplodeWhenRunOverEffect::HookedDamageAffectsPed(CEventDamage* thisDamage, void* edx, CPed* ped) {
	return !hasRunOverPed;
}
