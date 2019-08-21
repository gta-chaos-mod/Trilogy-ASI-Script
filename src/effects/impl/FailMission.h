// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/EffectPlaceholder.h"

#include "extensions/ScriptCommands.h"

class FailMission : public EffectPlaceholder
{
private:
	bool* onMission = reinterpret_cast<bool*>(0xA49FC4);

public:
	FailMission(int _duration, std::string _description);

	void Enable() override;
};
