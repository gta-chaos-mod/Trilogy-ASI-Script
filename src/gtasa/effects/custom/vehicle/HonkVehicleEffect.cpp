#include "HonkVehicleEffect.h"

HonkVehicleEffect::HonkVehicleEffect()
	: EffectBase("effect_honk_vehicle") {}

void HonkVehicleEffect::InitializeHooks() {
	HookCall(0x500366, HookedPlayHornOrSiren);
}

void HonkVehicleEffect::Disable() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_vehicleAudio.field_BE = true;
		vehicle->m_vehicleAudio.m_bSirenOrAlarmPlaying = true;
		vehicle->m_vehicleAudio.m_bHornPlaying = false;
	}

	EffectBase::Disable();
}

void HonkVehicleEffect::HandleTick() {
	EffectBase::HandleTick();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nHornCounter = 1;
	}
}

char __fastcall HonkVehicleEffect::HookedPlayHornOrSiren(CAEVehicleAudioEntity* thisAudioEntity, void* edx, char counter, char sirenOrAlarm, char playHorn, cVehicleParams* data) {
	bool siren = thisAudioEntity->m_bModelWithSiren;
	int _counter = siren ? 0 : 1;
	return CallMethodAndReturn<char, 0x4F99D0, CAEVehicleAudioEntity*>(thisAudioEntity, _counter, siren, false, data);
}
