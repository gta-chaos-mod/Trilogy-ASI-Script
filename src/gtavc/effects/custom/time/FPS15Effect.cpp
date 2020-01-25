#include "FPS15Effect.h"

byte FPS15Effect::oldFrameTimeWait = 0;

FPS15Effect::FPS15Effect()
	: EffectBase("effect_fps_15")
{
	AddType("framerate");
}

void FPS15Effect::Enable() {
	EffectBase::Enable();

	oldFrameTimeWait = injector::ReadMemory<byte>(0x53E94C, true);
	injector::WriteMemory<byte>(0x53E94C, 0, true);

	oldFramerate = RsGlobal.maxFPS;
}

void FPS15Effect::Disable() {
	injector::WriteMemory<byte>(0x53E94C, oldFrameTimeWait, true);
	RsGlobal.maxFPS = oldFramerate;

	EffectBase::Disable();
}

void FPS15Effect::HandleTick() {
	EffectBase::HandleTick();

	RsGlobal.maxFPS = framerate;
}
