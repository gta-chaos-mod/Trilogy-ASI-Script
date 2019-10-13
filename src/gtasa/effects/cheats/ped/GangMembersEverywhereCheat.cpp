#include "GangMembersEverywhereCheat.h"

GangMembersEverywhereCheat::GangMembersEverywhereCheat()
	: TimedFunctionEffect("cheat_gang_members_everywhere", CCheat::GangsCheat, 0x96915A)
{
	AddType("ped_spawns");
}
