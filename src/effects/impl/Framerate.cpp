// Copyright (c) 2019 Lordmau5
#include "Framerate.h"

byte Framerate::oldFrameTimeWait = 0;

Framerate::Framerate(int _framerate, int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "framerate") {
	framerate = _framerate;
}

void Framerate::Enable() {
	oldFrameTimeWait = injector::ReadMemory<byte>(0x53E94C, true);
	injector::WriteMemory<byte>(0x53E94C, 0, true);

	oldFramerate = RsGlobal.frameLimit;
}

void Framerate::Disable() {
	injector::WriteMemory<byte>(0x53E94C, oldFrameTimeWait, true);
	RsGlobal.frameLimit = oldFramerate;

	TimedEffect::Disable();
}

void Framerate::HandleTick() {
	RsGlobal.frameLimit = framerate;

	GenericUtil::SetVehiclesRealPhysics();
}
