// Copyright (c) 2019 Lordmau5
#include "Ped.h"

void Ped::SetAllOnFire() {
	for (CPed* ped : CPools::ms_pPedPool) {
		gFireManager.StartFire(ped, NULL, 1.0f, 1, 7000, 100);
	}
}

void Ped::ClearWeapons() {
	for (CPed* ped : CPools::ms_pPedPool) {
		ped->ClearWeapons();
	}
}
