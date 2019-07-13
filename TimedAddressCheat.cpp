#include "TimedAddressCheat.h"

TimedAddressCheat::TimedAddressCheat(int _address, int duration, std::string description) : TimedEffect(duration, description) {
	address = reinterpret_cast<bool*>(_address);
}

void TimedAddressCheat::Enable() {
	if (address != nullptr) {
		*address = true;
	}
}

void TimedAddressCheat::Disable() {
	if (address != nullptr) {
		*address = false;
	}
}