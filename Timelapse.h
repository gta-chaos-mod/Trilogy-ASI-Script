#pragma once

#include "TimedEffect.h"

#include "CClock.h"

class Timelapse : public TimedEffect
{
public:
	Timelapse(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;
};
