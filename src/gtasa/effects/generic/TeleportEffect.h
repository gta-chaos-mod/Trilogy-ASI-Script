#pragma once

#include "util/EffectBase.h"

#include "util/Teleportation.h"

class TeleportEffect : public EffectBase
{
private:
	CVector destination = CVector();
	bool hasTeleported = false;

public:
	TeleportEffect(CVector destination);

	bool CanActivate() override;

	void HandleTick() override;
};
