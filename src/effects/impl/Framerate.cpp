// Copyright (c) 2019 Lordmau5
#include "Framerate.h"

byte* Framerate::frameTimeWait = reinterpret_cast<byte*>(0x53E94C);

Framerate::Framerate(int _framerate, int _duration, std::string _description)
	: TimedEffect(_duration, _description, "framerate") {
	framerate = _framerate;
}

void Framerate::Enable() {
	*Framerate::frameTimeWait = 0;
	oldFramerate = RsGlobal.frameLimit;
}

void Framerate::Disable() {
	*Framerate::frameTimeWait = 14;
	RsGlobal.frameLimit = oldFramerate;

	TimedEffect::Disable();
}

void Framerate::HandleTick() {
	RsGlobal.frameLimit = framerate;
}
