#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCheat.h"

class HaveABountyOnYourHeadCheat : public EffectBase
{
private:
	bool* haveABountyOnYourHeadCheat = reinterpret_cast<bool*>(0x96913F);

public:
	HaveABountyOnYourHeadCheat();

	void Enable() override;
	void Disable() override;
};
