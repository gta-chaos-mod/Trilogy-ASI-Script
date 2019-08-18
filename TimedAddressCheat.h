// Copyright (c) 2019 Lordmau5
#pragma once

#include "TimedEffect.h"

class TimedAddressCheat : public TimedEffect
{
public:
	bool* address = nullptr;

public:
	TimedAddressCheat(int _address, int duration, std::string description);
	TimedAddressCheat(int _address, int duration, std::string description, std::string type);

	void Disable() override;

	void HandleTick() override;
};
