#pragma once

#include "TimedEffect.h"

class EverybodyBleedNow : public TimedEffect
{
public:
	EverybodyBleedNow(int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;
};