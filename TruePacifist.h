#pragma once

#include "TimedEffect.h"

class TruePacifist : public TimedEffect
{
public:
	static bool isEnabled;

public:
	TruePacifist(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;
};
