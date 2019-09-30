// Copyright (c) 2019 Lordmau5
#pragma once

#include <map>

#include "effects/abstract/EffectPlaceholder.h"

#include "effects/other/Player.h"
#include "effects/other/Teleportation.h"

#include "CCutsceneMgr.h"
#include "extensions/ScriptCommands.h"

class PassMission : public EffectPlaceholder
{
private:
	static bool isEnabled;

private:
	std::map<std::string, int> offsetMap = {};
	std::map<std::string, bool> debugCodeMap = {};
	bool triedPassingMission = false;
	int missionPassWait = 100;

public:
	PassMission(int _duration, const std::string& _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	void ClearPlayerStatus();

	static char __stdcall HookedDebugGetKeyDown(int keyCode, int a2, int a3);
};
