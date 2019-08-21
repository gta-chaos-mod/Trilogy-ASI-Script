// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CControllerConfigManager.h"
#include "CFileMgr.h"

class InvertedControls : public TimedEffect
{
public:
	static bool isEnabled;

private:
	int wait = 0;
	CControllerAction origActions[59];
	CControllerAction invertedActions[59];

public:
	InvertedControls(int _duration, std::string _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	static FILESTREAM HookedOpenFile(const char* file, const char* mode);

private:
	void SwapControls(e_ControllerAction source, e_ControllerAction target);
};
