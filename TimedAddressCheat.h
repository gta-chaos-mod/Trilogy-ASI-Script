#pragma once

#include "TimedEffect.h"

class TimedAddressCheat : public TimedEffect
{
public:
	bool* address = nullptr;

public:
	TimedAddressCheat(int _address, int duration, std::string description);

	void Disable() override;

	void HandleTick() override;
};
