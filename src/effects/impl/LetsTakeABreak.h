// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CControllerConfigManager.h"
#include "CFileMgr.h"

class LetsTakeABreak : public TimedEffect
{
public:
	static bool isEnabled;

private:
	int wait = 0;
	int effectRemaining = 1000 * 10;
	CControllerAction origActions[59];

public:
	LetsTakeABreak(int _duration, std::string _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	int GetRemaining() override;

	void HandleTick() override;

	static FILESTREAM HookedOpenFile(const char* file, const char* mode);
};
