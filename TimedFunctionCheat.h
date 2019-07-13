#pragma once

#include "TimedEffect.h"

class TimedFunctionCheat : public TimedEffect
{
public:
	void* function = nullptr;

public:
	TimedFunctionCheat(void* _function, int duration, std::string description);

	void Enable() override;
	void Disable() override;
};
