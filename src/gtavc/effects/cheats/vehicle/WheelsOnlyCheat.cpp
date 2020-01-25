#include "WheelsOnlyCheat.h"

WheelsOnlyCheat::WheelsOnlyCheat()
	: TimedAddressEffect("cheat_wheels_only", 0xA10B30)
{
	AddType("invisible_vehicles");
}
