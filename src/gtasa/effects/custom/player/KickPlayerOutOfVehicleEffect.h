#pragma once

#include "effects/EffectPlaceholder.h"

#include "extensions/ScriptCommands.h"

class KickPlayerOutOfVehicleEffect : public EffectPlaceholder
{
public:
	KickPlayerOutOfVehicleEffect();

	bool CanActivate() override;

	void Enable() override;
};
