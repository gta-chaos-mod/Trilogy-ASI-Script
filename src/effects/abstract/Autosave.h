// Copyright (c) 2019 Lordmau5
#pragma once

#include "TimedEffect.h"

#include "util/GenericUtil.h"

class Autosave : public TimedEffect
{
private:
	bool didSave = false;
	int missionsPassed = 0;

public:
	Autosave(int _missionsPassed);

	void HandleTick() override;
};
