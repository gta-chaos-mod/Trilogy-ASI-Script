#include "BlackCarsCheat.h"

BlackCarsCheat::BlackCarsCheat()
	: TimedFunctionEffect("cheat_black_cars", CCheat::BlackCarsCheat, 0x969151)
{
	AddType("traffic_color");
}
