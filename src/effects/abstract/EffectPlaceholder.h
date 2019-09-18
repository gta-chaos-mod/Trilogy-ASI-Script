// Copyright (c) 2019 Lordmau5
#pragma once

#include "TimedEffect.h"

class EffectPlaceholder : public TimedEffect
{
public:
	EffectPlaceholder(int _duration, const std::string& _description);
	EffectPlaceholder(int _duration, const std::string& _description, const char* _type);
};
