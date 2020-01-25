#include "InfiniteHealthEveryoneEffect.h"

InfiniteHealthEveryoneEffect::InfiniteHealthEveryoneEffect()
	: EffectBase("effect_infinite_health_everyone")
{
	AddType("health");
}

void InfiniteHealthEveryoneEffect::InitializeHooks() {
	EffectBase::InitializeHooks();

	for (int address : {
		0x48E787, 0x48E7AD, 0x4AC800, 0x4D4EDE, 0x4D81EE, 0x4FD248, 0x5053E7, 0x505465, 0x5064F9,
			0x509776, 0x50997A, 0x5245D5, 0x524741, 0x527BAB, 0x599F48, 0x599F98, 0x5A0E0B, 0x5B49AA,
			0x5C4089, 0x5C9DBE, 0x5CBC95, 0x5CE361, 0x5CF34B, 0x5CF54A, 0x5CF54A, 0x5D3352, 0x6137BD,
			0x613887, 0x614C49, 0x614CC0
	}) {
		HookCall(address, HookedCPedInflictDamage);
	}
}

void InfiniteHealthEveryoneEffect::HandleTick() {
	EffectBase::HandleTick();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_fHealth = 100.0f;
	}
}

bool __fastcall InfiniteHealthEveryoneEffect::HookedCPedInflictDamage(CPed* thisPed, void* edx, CEntity* source, eWeaponType weapon, float damage, ePedPieceTypes pedPiece, uchar unknown) {
	return false;
}
