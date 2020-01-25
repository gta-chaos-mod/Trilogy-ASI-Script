#include "RingRingEffect.h"

RingRingEffect::RingRingEffect()
	: EffectBase("effect_ring_ring")
{
	SetEffectDuration(1000 * 30);
}

bool RingRingEffect::CanActivate() {
	CVehicle* vehicle = FindPlayerVehicle(-1, false);

	return FindPlayerPed() && !vehicle;
}

void RingRingEffect::Disable() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		Command<eScriptCommands::COMMAND_TASK_USE_MOBILE_PHONE>(FindPlayerPed(), false);
	}

	EffectBase::Disable();
}

void RingRingEffect::HandleTick() {
	EffectBase::HandleTick();

	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		CTask* phoneTask = player->m_pIntelligence->m_TaskMgr.FindTaskByType(3, 1600);
		if (!phoneTask)
		{
			CStreaming::RequestModel(330, 2);
			CStreaming::LoadAllRequestedModels(0);

			CStreaming::SetModelIsDeletable(330);

			Command<eScriptCommands::COMMAND_TASK_USE_MOBILE_PHONE>(FindPlayerPed(), true);
			wait = 1000;
		}
	}
}
