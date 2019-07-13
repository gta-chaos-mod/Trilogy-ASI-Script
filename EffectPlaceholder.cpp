#include "EffectPlaceholder.h"

EffectPlaceholder::EffectPlaceholder(int _duration, std::string _description) : TimedEffect(_duration, _description) {
	isPlaceholder = true;
}