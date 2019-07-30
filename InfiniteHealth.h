#pragma once

#include "TimedEffect.h"

class InfiniteHealth : public TimedEffect
{
public:
	static bool isEnabled;

public:
	InfiniteHealth(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;
};
