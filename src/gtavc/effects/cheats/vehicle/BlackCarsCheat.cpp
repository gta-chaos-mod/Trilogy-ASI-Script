#include "BlackCarsCheat.h"

BlackCarsCheat::BlackCarsCheat()
	: TimedAddressEffect("cheat_black_cars", 0xA10B82)
{
	AddType("traffic_color");
}
