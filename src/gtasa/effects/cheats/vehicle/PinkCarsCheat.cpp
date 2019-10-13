#include "PinkCarsCheat.h"

PinkCarsCheat::PinkCarsCheat()
	: TimedFunctionEffect("cheat_pink_cars", CCheat::PinkCarsCheat, 0x969150)
{
	AddType("traffic_color");
}
