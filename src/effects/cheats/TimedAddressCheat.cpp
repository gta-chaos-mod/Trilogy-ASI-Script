// Copyright (c) 2019 Lordmau5
#include "TimedAddressCheat.h"

TimedAddressCheat::TimedAddressCheat(int _address, int _duration, const std::string& _description)
	: TimedEffect(_duration, _description) {
	address = reinterpret_cast<bool*>(_address);
}

TimedAddressCheat::TimedAddressCheat(int _address, int _duration, const std::string& _description, const char* _type)
	: TimedAddressCheat(_address, _duration, _description) {
	type = _type;
}

void TimedAddressCheat::Disable() {
	if (address) {
		*address = false;
	}

	TimedEffect::Disable();
}

void TimedAddressCheat::HandleTick() {
	if (address) {
		*address = true;
	}
}
