#include "DisableHUD.h"

bool DisableHUD::isEnabled = false;

DisableHUD::DisableHUD(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void DisableHUD::Enable() {
	isEnabled = true;
}

void DisableHUD::Disable() {
	isEnabled = false;
}
