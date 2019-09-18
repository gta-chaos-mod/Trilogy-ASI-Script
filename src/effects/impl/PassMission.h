// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/EffectPlaceholder.h"

class PassMission : public EffectPlaceholder
{
private:
	int wait = 100;

public:
	static bool isEnabled;

public:
	PassMission(int _duration, const std::string& _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	static char __stdcall HookedDebugGetKeyDown(int keyCode, int a2, int a3);
};
