#pragma once

#include "effects/EffectPlaceholder.h"

#include "util/EffectDatabase.h"
#include "util/GameUtil.h"
#include "util/Teleportation.h"

#include "effects/generic/AutosaveEffect.h"

#include "CGangWars.h"
#include "CTheScripts.h"
#include "extensions/ScriptCommands.h"

class FakePassCurrentMissionEffect : public EffectPlaceholder
{
private:
	bool handledEverything = false;
	bool handledMission = false;
	bool lastIsOnMission = false;

	int wait = 500;

public:
	FakePassCurrentMissionEffect();

	void HandleTick() override;

	void ClearPlayerStatus();
};
