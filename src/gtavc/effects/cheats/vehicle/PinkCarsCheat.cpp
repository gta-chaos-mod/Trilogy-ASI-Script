#include "PinkCarsCheat.h"

PinkCarsCheat::PinkCarsCheat()
	: TimedAddressEffect("cheat_pink_cars", 0xA10B26)
{
	AddType("traffic_color");
}
