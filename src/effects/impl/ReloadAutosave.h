// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/EffectPlaceholder.h"

#include "effects/impl/HookHandler.h"

class ReloadAutosave : public EffectPlaceholder
{
public:
	ReloadAutosave(int _duration, std::string _description);

	void Enable() override;
};
