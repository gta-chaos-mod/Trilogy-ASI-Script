// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

class TimedAddressCheat : public TimedEffect
{
public:
	bool* address = nullptr;

public:
	TimedAddressCheat(int _address, int duration, const std::string& description);
	TimedAddressCheat(int _address, int duration, const std::string& description, const char* type);

	void Disable() override;

	void HandleTick() override;
};
