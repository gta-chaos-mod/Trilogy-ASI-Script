#include "TimedAddressCheat.h"

TimedAddressCheat::TimedAddressCheat(int _address, int _duration, std::string _description)
	: TimedEffect(_duration, _description) {
	address = reinterpret_cast<bool*>(_address);
}

TimedAddressCheat::TimedAddressCheat(int _address, int _duration, std::string _description, std::string _type)
	: TimedAddressCheat(_address, _duration, _description) {
	type = _type;
}

void TimedAddressCheat::Disable() {
	if (address != nullptr) {
		*address = false;
	}
}

void TimedAddressCheat::HandleTick() {
	if (address != nullptr) {
		*address = true;
	}
}