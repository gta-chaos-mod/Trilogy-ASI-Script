#include "PedsAttackEachOtherCheat.h"

PedsAttackEachOtherCheat::PedsAttackEachOtherCheat()
	: EffectBase("cheat_peds_attack_each_other")
{
	AddType("peds_attack");
	SetDisabledForMissions();
}

void PedsAttackEachOtherCheat::Enable() {
	EffectBase::Enable();

	GameUtil::BackupAcquaintances();

	if (!*pedsAttackEachOtherCheat) {
		CCheat::MayhemCheat();
	}
}

void PedsAttackEachOtherCheat::Disable() {
	if (*pedsAttackEachOtherCheat) {
		CCheat::MayhemCheat();
	}

	GameUtil::RestoreSavedAcquaintances();

	EffectBase::Disable();
}
