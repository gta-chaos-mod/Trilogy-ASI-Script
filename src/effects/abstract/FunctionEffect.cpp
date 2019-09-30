// Copyright (c) 2019 Lordmau5
#include "FunctionEffect.h"

FunctionEffect::FunctionEffect(void* _function, int _duration, const std::string& _description)
	: EffectPlaceholder(_duration, _description) {
	function = _function;
}

FunctionEffect::FunctionEffect(void* _function, int _duration, const std::string& _description, const char* _type)
	: FunctionEffect(_function, _duration, _description) {
	AddType(_type);
}

void FunctionEffect::Enable() {
	if (function) {
		reinterpret_cast<void(*)()> (function) ();
	}
}
