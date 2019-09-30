// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/EffectPlaceholder.h"

#include "effects/other/Player.h"

#include "CGangWars.h"
#include "CTheScripts.h"
#include "extensions/ScriptCommands.h"

class FailMission : public EffectPlaceholder
{
private:
	bool fakePass = false;

	bool handledEverything = false;
	bool handledMission = false;
	bool lastIsOnMission = false;

	int wait = 500;

public:
	FailMission(bool _fakePass, int _duration, const std::string& _description);

	void HandleTick() override;
};
