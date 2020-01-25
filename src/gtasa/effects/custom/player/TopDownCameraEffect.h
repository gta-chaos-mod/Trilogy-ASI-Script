#pragma once

#include "util/EffectBase.h"
#include "util/Teleportation.h"

#include "CCamera.h"
#include "extensions/ScriptCommands.h"

class TopDownCameraEffect : public EffectBase
{
public:
	TopDownCameraEffect();

	bool CanActivate() override;

	void Disable() override;

	void HandleTick() override;
};
