#pragma once

#include "TimedEffect.h"

class LetsTakeABreak : public TimedEffect
{
public:
	LetsTakeABreak(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;
};

