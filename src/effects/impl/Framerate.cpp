// Copyright (c) 2019 Lordmau5
#include "Framerate.h"

Framerate::Framerate(int _framerate, int _duration, std::string _description)
	: TimedEffect(_duration, _description, "framerate") {
	framerate = _framerate;
}

void Framerate::Enable() {
	oldFramerate = RsGlobal.frameLimit;
}

void Framerate::Disable() {
	RsGlobal.frameLimit = oldFramerate;

	TimedEffect::Disable();
}

void Framerate::HandleTick() {
	RsGlobal.frameLimit = framerate;
}
