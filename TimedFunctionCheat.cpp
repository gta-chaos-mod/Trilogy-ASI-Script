#include "TimedFunctionCheat.h"

TimedFunctionCheat::TimedFunctionCheat(void* _function, int _address, int _duration, std::string _description) : TimedEffect(_duration, _description) {
	function = _function;
	address = reinterpret_cast<bool*>(_address);
}

TimedFunctionCheat::TimedFunctionCheat(void* _function, int _address, int _duration, std::string _description, std::string _type) : TimedFunctionCheat(_function, _address, _duration, _description) {
	type = _type;
}

void TimedFunctionCheat::Disable() {
	if (function && address && *address) {
		reinterpret_cast<void(*)()> (function) ();
	}
}

void TimedFunctionCheat::HandleTick() {
	if (function && address && !*address) {
		reinterpret_cast<void(*)()> (function) ();
	}
}