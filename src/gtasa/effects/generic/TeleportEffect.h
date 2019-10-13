#pragma once

#include "effects/EffectPlaceholder.h"

#include "util/Teleportation.h"

class TeleportEffect : public EffectPlaceholder
{
private:
	CVector destination;

public:
	TeleportEffect(CVector destination);

	void Enable() override;
};
