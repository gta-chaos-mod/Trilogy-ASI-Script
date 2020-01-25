#include "FPS60Effect.h"

byte FPS60Effect::oldFrameTimeWait = 0;

FPS60Effect::FPS60Effect()
	: EffectBase("effect_fps_15")
{
	AddType("framerate");
}

void FPS60Effect::Enable() {
	EffectBase::Enable();

	oldFrameTimeWait = injector::ReadMemory<byte>(0x53E94C, true);
	injector::WriteMemory<byte>(0x53E94C, 0, true);

	oldFramerate = RsGlobal.maxFPS;
}

void FPS60Effect::Disable() {
	injector::WriteMemory<byte>(0x53E94C, oldFrameTimeWait, true);
	RsGlobal.maxFPS = oldFramerate;

	EffectBase::Disable();
}

void FPS60Effect::HandleTick() {
	EffectBase::HandleTick();

	RsGlobal.maxFPS = framerate;
}
