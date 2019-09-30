// Copyright (c) 2019 Lordmau5
#include "HaveABountyOnYourHead.h"

HaveABountyOnYourHead::HaveABountyOnYourHead(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description) {}

void HaveABountyOnYourHead::Enable() {
	TimedEffect::Enable();

	GenericUtil::BackupAcquaintances();

	if (!*haveABountyOnYourHeadCheat) {
		CCheat::EverybodyAttacksPlayerCheat();
	}
}

void HaveABountyOnYourHead::Disable() {
	if (*haveABountyOnYourHeadCheat) {
		CCheat::EverybodyAttacksPlayerCheat();
	}

	GenericUtil::RestoreSavedAcquaintances();

	TimedEffect::Disable();
}
