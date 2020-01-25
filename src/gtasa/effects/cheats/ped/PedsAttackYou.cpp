#include "PedsAttackYou.h"

PedsAttackYou::PedsAttackYou()
	: TimedFunctionEffect("cheat_peds_attack_you", CCheat::VillagePeopleCheat, 0x969158)
{
	AddType("peds_attack");
	SetDisabledForMissions();
}
