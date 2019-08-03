#pragma once

#include "TimedEffect.h"

class EffectPlaceholder : public TimedEffect
{
public:
	EffectPlaceholder(int _duration, std::string _description);
	EffectPlaceholder(int _duration, std::string _description, std::string _type);
};
