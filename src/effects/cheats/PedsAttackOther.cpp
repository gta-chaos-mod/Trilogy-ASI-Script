// Copyright (c) 2019 Lordmau5
#include "PedsAttackOther.h"

PedsAttackOther::PedsAttackOther(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description) {}

void PedsAttackOther::Enable() {
	TimedEffect::Enable();

	GenericUtil::BackupAcquaintances();

	if (!*pedsAttackOtherCheat) {
		CCheat::MayhemCheat();
	}
}

void PedsAttackOther::Disable() {
	if (*pedsAttackOtherCheat) {
		CCheat::MayhemCheat();
	}

	GenericUtil::RestoreSavedAcquaintances();

	TimedEffect::Disable();
}
