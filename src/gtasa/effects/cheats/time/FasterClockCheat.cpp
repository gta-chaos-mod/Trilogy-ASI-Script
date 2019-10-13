#include "FasterClockCheat.h"

FasterClockCheat::FasterClockCheat()
	: TimedAddressEffect("cheat_faster_clock", 0x96913B)
{
	AddType("time");
}
