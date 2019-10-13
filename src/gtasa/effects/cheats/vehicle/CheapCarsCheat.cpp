#include "CheapCarsCheat.h"

CheapCarsCheat::CheapCarsCheat()
	: TimedFunctionEffect("cheat_cheap_cars", CCheat::AllCarsAreShitCheat, 0x96915E)
{
	AddType("vehicle_rarity");
}
