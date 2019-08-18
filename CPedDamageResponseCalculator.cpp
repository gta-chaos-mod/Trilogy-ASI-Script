// Copyright (c) 2019 Lordmau5
#include "CPedDamageResponseCalculator.h"

unsigned int CPedDamageResponseCalculator::AccountForPedArmour(CPed* a2, int cDamageResponseInfo) {
	return plugin::CallMethodAndReturn<unsigned int, 0x4AD550, CPedDamageResponseCalculator*>(this, a2, cDamageResponseInfo);
}

void CPedDamageResponseCalculator::ComputeWillKillPed(CPed* a2, float* a3, char a4) {
	plugin::CallMethod<0x4B3210, CPedDamageResponseCalculator*>(this, a2, a3, a4);
}
