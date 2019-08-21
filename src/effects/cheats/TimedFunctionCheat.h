// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

class TimedFunctionCheat : public TimedEffect
{
public:
	void* function = nullptr;
	bool* address = nullptr;

public:
	TimedFunctionCheat(void* _function, int _address, int _duration, std::string _description);
	TimedFunctionCheat(void* _function, int _address, int _duration, std::string _description, std::string _type);

	void Disable() override;

	void HandleTick() override;
};
