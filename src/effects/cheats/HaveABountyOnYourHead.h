// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "util/GenericUtil.h"

#include "CCheat.h"

class HaveABountyOnYourHead : public TimedEffect
{
private:
	bool* haveABountyOnYourHeadCheat = reinterpret_cast<bool*>(0x96913F);

public:
	HaveABountyOnYourHead(int _duration, const std::string& _description);

	void Enable() override;
	void Disable() override;
};
