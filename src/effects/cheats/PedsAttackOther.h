// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "util/GenericUtil.h"

#include "CCheat.h"

class PedsAttackOther : public TimedEffect
{
private:
	bool* pedsAttackOtherCheat = reinterpret_cast<bool*>(0x96913E);

public:
	PedsAttackOther(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;
};
