#include "TruePacifist.h"

bool TruePacifist::isEnabled = false;

TruePacifist::TruePacifist(int _duration, std::string _description)
	: TimedEffect(_duration, _description, "health") {}

void TruePacifist::Enable() {
	isEnabled = true;
}

void TruePacifist::Disable() {
	isEnabled = false;
}
