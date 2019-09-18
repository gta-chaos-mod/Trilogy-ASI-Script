// Copyright (c) 2019 Lordmau5
#include "OneHitKO.h"

OneHitKO::OneHitKO(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "health") {}

void OneHitKO::Disable() {
	*neverHungryCheat = false;

	TimedEffect::Disable();
}

void OneHitKO::HandleTick() {
	*neverHungryCheat = true;

	for (CPed* ped : CPools::ms_pPedPool) {
		ped->m_fHealth = max(0.0f, min(ped->m_fHealth, 1.0f));
		ped->m_fArmour = 0.0f;
	}
}
