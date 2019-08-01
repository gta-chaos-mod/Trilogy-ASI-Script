#include "FunctionEffect.h"

FunctionEffect::FunctionEffect(void* _function, int _duration, std::string _description) : EffectPlaceholder(_duration, _description) {
	function = _function;
}

FunctionEffect::FunctionEffect(void* _function, int _duration, std::string _description, std::string _type) : FunctionEffect(_function, _duration, _description) {
	type = _type;
}

void FunctionEffect::Enable() {
	if (function) {
		reinterpret_cast<void(*)()> (function) ();
	}
}