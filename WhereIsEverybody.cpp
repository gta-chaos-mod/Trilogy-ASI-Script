#include "WhereIsEverybody.h"

WhereIsEverybody::WhereIsEverybody(int _duration, std::string _description)
	: TimedEffect(_duration, _description) {}

void WhereIsEverybody::InitializeHooks() {
	patch::RedirectCall(0x5E6900, HookedRenderPedShadow);
}

void WhereIsEverybody::Disable() {
	for (CPed* ped : CPools::ms_pPedPool) {
		ped->m_nPedFlags.bDontRender = false;
	}
}

void WhereIsEverybody::HandleTick() {
	for (CPed* ped : CPools::ms_pPedPool) {
		ped->m_nPedFlags.bDontRender = true;
	}
}

void WhereIsEverybody::HookedRenderPedShadow(CPed* thisPed, float disp_x, float disp_y, float front_x, float front_y, float side_x, float side_y) {
	if (!thisPed->m_nPedFlags.bDontRender) {
		CShadows::StoreShadowForPedObject(thisPed, disp_x, disp_y, front_x, front_y, side_x, side_y);
	}
}
