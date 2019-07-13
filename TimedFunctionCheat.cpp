#include "TimedFunctionCheat.h"

TimedFunctionCheat::TimedFunctionCheat(void* _function, int duration, std::string description) : TimedEffect(duration, description) {
	function = _function;
}

void TimedFunctionCheat::Enable() {
	if (function != nullptr) {
		reinterpret_cast<void(*)()> (function) ();
	}
}

void TimedFunctionCheat::Disable() {
	if (function != nullptr) {
		reinterpret_cast<void(*)()> (function) ();
	}
}