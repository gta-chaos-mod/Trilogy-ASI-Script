#include "TimedAddressCheat.h"

TimedAddressCheat::TimedAddressCheat(int _address, int duration, std::string description) : TimedEffect(duration, description) {
	address = reinterpret_cast<bool*>(_address);
}

TimedAddressCheat::TimedAddressCheat(int _address, int duration, std::string description, std::string _type) : TimedAddressCheat(_address, duration, description) {
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