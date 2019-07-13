#include "Ped.h"

void Ped::SetAllOnFire() {
	for (CPed* ped : CPools::ms_pPedPool) {
		gFireManager.StartFire(ped, NULL, 1.0f, 1, 7000, 100);
	}
}