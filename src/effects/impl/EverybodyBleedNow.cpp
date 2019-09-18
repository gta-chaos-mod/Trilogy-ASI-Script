// Copyright (c) 2019 Lordmau5
#include "EverybodyBleedNow.h"

EverybodyBleedNow::EverybodyBleedNow(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "health") {}

void EverybodyBleedNow::Disable() {
	*neverHungryCheat = false;

	for (CPed* ped : CPools::ms_pPedPool) {
		ped->m_nPedFlags.bDoBloodyFootprints = false;
		ped->m_nPedFlags.bPedIsBleeding = false;
	}

	TimedEffect::Disable();
}

void EverybodyBleedNow::HandleTick() {
	bool isLosingHealth = false;

	*neverHungryCheat = true;

	wait -= CalculateTick();
	if (wait < 0) {
		wait = 3000;
		isLosingHealth = true;
	}

	for (CPed* ped : CPools::ms_pPedPool) {
		ped->m_nPedFlags.bDoBloodyFootprints = true;
		ped->m_nPedFlags.bPedIsBleeding = true;

		if (isLosingHealth) {
			ped->m_fHealth -= RandomHelper::Random(1.0f, 3.0f);
		}
	}
}
