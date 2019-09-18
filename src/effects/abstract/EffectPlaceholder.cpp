// Copyright (c) 2019 Lordmau5
#include "EffectPlaceholder.h"

EffectPlaceholder::EffectPlaceholder(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description) {
	isPlaceholder = true;
}

EffectPlaceholder::EffectPlaceholder(int _duration, const std::string& _description, const char* _type)
	: EffectPlaceholder(_duration, _description) {
	type = _type;
}
