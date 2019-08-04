#pragma once

#include "EffectPlaceholder.h"

class PassMission : public EffectPlaceholder
{
private:
	int wait = 3000;

public:
	static bool isEnabled;

public:
	PassMission(int _duration, std::string _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	static char __stdcall HookedDebugGetKeyDown(int keyCode, int a2, int a3);
};
