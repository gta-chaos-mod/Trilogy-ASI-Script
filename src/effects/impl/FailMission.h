// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/EffectPlaceholder.h"

#include "extensions/ScriptCommands.h"

class FailMission : public EffectPlaceholder
{
public:
	FailMission(int _duration, std::string _description);

	void Enable() override;
};
