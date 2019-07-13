#pragma once

#include "common.h"
#include "plugin.h"

#include "CPools.h"
#include "CCarCtrl.h"

#include "TimedEffect.h"

class Gravity : public TimedEffect
{
public:
	Gravity(float gravity, int duration, std::string description);

	void Enable();
	void Disable();
};
