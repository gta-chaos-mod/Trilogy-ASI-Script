#include "EverybodyBleedNow.h"

EverybodyBleedNow::EverybodyBleedNow(int _duration, std::string _description)
	: TimedEffect(_duration, _description) {}

void EverybodyBleedNow::Disable() {
	for (CPed* ped : CPools::ms_pPedPool) {
		ped->m_nPedFlags.bDoBloodyFootprints = false;
		ped->m_nPedFlags.bPedIsBleeding = false;
	}
}

void EverybodyBleedNow::HandleTick() {
	for (CPed* ped : CPools::ms_pPedPool) {
		ped->m_nPedFlags.bDoBloodyFootprints = true;
		ped->m_nPedFlags.bPedIsBleeding = true;
	}
}
