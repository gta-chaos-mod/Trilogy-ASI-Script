#include "InfiniteHealth.h"

bool InfiniteHealth::isEnabled = false;

InfiniteHealth::InfiniteHealth(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void InfiniteHealth::Enable() {
	isEnabled = true;
}

void InfiniteHealth::Disable() {
	isEnabled = false;
}
