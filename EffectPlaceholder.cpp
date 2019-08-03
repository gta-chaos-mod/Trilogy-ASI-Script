#include "EffectPlaceholder.h"

EffectPlaceholder::EffectPlaceholder(int _duration, std::string _description)
	: TimedEffect(_duration, _description) {
	isPlaceholder = true;
}

EffectPlaceholder::EffectPlaceholder(int _duration, std::string _description, std::string _type)
	: EffectPlaceholder(_duration, _description) {
	type = _type;
}
