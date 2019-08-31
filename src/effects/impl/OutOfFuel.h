// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/EffectPlaceholder.h"

#include "effects/other/Vehicle.h"

#include "CCarCtrl.h"

class OutOfFuel : public EffectPlaceholder
{
public:
	OutOfFuel(int _duration, std::string _description);

	void Enable() override;
};
