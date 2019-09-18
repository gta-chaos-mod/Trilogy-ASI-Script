// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/EffectPlaceholder.h"

class ReloadAutosave : public EffectPlaceholder
{
public:
	ReloadAutosave(int _duration, const std::string& _description);

	void Enable() override;
};
