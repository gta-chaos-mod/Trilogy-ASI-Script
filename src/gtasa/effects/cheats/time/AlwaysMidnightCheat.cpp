#include "AlwaysMidnightCheat.h"

AlwaysMidnightCheat::AlwaysMidnightCheat()
	: TimedAddressEffect("cheat_always_midnight", 0x969167)
{
	AddType("time");
}

void AlwaysMidnightCheat::HandleTick() {
	TimedAddressEffect::HandleTick();

	CClock::ms_nGameClockHours = 0;
	CClock::ms_nGameClockMinutes = 0;
	CClock::ms_nGameClockSeconds = 0;
}
