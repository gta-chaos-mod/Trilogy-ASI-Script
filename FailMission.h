#pragma once

#include "common.h"
#include "plugin.h"

#include "extensions/ScriptCommands.h"

#include "EffectPlaceholder.h"

class FailMission : public EffectPlaceholder
{
public:
	FailMission(int _duration, std::string _description);

	void Enable() override;
};
