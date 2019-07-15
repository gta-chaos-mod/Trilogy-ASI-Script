#include "TimedAddressCheat.h"

TimedAddressCheat::TimedAddressCheat(int _address, int duration, std::string description) : TimedEffect(duration, description) {
	address = reinterpret_cast<bool*>(_address);
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