#include "Ped.h"

void Ped::SetAllOnFire() {
	if (CPools::ms_pPedPool->m_nSize == 0) {
		return;
	}

	for (CPed* ped : CPools::ms_pPedPool) {
		gFireManager.StartFire(ped, NULL, 1.0f, 1, 7000, 100);
	}
}