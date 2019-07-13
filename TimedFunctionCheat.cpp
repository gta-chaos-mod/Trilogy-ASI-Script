#include "TimedFunctionCheat.h"

TimedFunctionCheat::TimedFunctionCheat(void* _function, int _address, int duration, std::string description) : TimedEffect(duration, description) {
	function = _function;
	address = reinterpret_cast<bool*>(_address);
}

void TimedFunctionCheat::Enable() {
	if (function != nullptr && address != nullptr && !*address) {
		reinterpret_cast<void(*)()> (function) ();
	}
}

void TimedFunctionCheat::Disable() {
	if (function != nullptr && address != nullptr && *address) {
		reinterpret_cast<void(*)()> (function) ();
	}
}