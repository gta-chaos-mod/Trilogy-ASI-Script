#pragma once

#include "TimedEffect.h"

class TimedFunctionCheat : public TimedEffect
{
public:
	void* function = nullptr;
	bool* address = nullptr;

public:
	TimedFunctionCheat(void* _function, int _address, int duration, std::string description);

	void Enable() override;
	void Disable() override;
};
