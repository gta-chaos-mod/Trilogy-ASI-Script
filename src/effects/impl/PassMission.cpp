// Copyright (c) 2019 Lordmau5
#include "PassMission.h"

bool PassMission::isEnabled = false;

PassMission::PassMission(int _duration, const std::string& _description)
	: EffectPlaceholder(_duration, _description) {}

void PassMission::InitializeHooks() {
	patch::RedirectCall(0x46DDED, HookedDebugGetKeyDown);
	patch::RedirectCall(0x46DE32, HookedDebugGetKeyDown);
}

void PassMission::Enable() {
	TimedEffect::Enable();

	/* Los Santos */
	offsetMap["INTRO1"] = 18131; // Big Smoke
	offsetMap["INTRO2"] = 13692; // Ryder

	offsetMap["SWEET1"] = 14682; // Tagging Up Turf

	offsetMap["SWEET1B"] = 8674; // Cleaning The Hood
	debugCodeMap["SWEET1B"] = true;

	offsetMap["SWEET3"] = 12908; // Drive-Thru
	offsetMap["SWEET2"] = 20304; // Nines And AK's
	offsetMap["SWEET4"] = 23785; // Drive-By
	offsetMap["HOODS5"] = 15274; // Sweet's Girl

	offsetMap["SWEET6"] = 147; // Cesar Vialpando
	debugCodeMap["SWEET6"] = true;

	offsetMap["SWEET7"] = 32422; // Los Sepulcros
	offsetMap["CRASH4"] = 6337; // Doberman

	offsetMap["CRASH1"] = 1199; // Burning Desire
	debugCodeMap["CRASH1"] = true;

	offsetMap["DRUGS3"] = 19361; // Gray Imports
	offsetMap["GUNS1"] = 40660; // Home Invasion

	offsetMap["RYDER3"] = 2254; // Catalyst
	debugCodeMap["RYDER3"] = true;

	offsetMap["RYDER2"] = 238; // Robbing Uncle Sam
	debugCodeMap["RYDER2"] = true;

	offsetMap["TWAR7"] = 23183; // OG Loc
	offsetMap["SMOKE2"] = 11352; // Running Dog
	offsetMap["SMOKE3"] = 20115; // Wrong Side Of The Tracks
	offsetMap["DRUGS1"] = 52043; // Just Business

	offsetMap["MUSIC1"] = 15574; // Life's a Beach
	offsetMap["MUSIC2"] = 10527; // Madd Dogg's Rhymes
	offsetMap["MUSIC3"] = 15510; // Management Issues
	offsetMap["MUSIC5"] = 15889; // House Party

	// offsetMap["CESAR1"] = 2251; // High Stakes, Low-rider

	offsetMap["DRUGS4"] = 67765; // Reuniting The Families

	offsetMap["LA1FIN2"] = 390; // The Green Sabre
	debugCodeMap["LA1FIN2"] = true;
	/* ######################### */

	/* Badlands */
	offsetMap["BCRASH1"] = 13609; // Badlands

	offsetMap["CAT1"] = 292; // Local Liquor Store
	debugCodeMap["CAT1"] = true;

	offsetMap["CAT2"] = 30025; // Small Town Bank
	debugCodeMap["CAT2"] = true;

	offsetMap["CAT3"] = 4141; // Tanker Commander
	debugCodeMap["CAT3"] = true;

	offsetMap["CAT4"] = 6648; // Against All Odds
	debugCodeMap["CAT4"] = true;

	offsetMap["TRUTH1"] = 16397; // Body Harvest
	offsetMap["TRUTH2"] = 11942; // Are You Going To San Fierro?

	/* No "Wu Zi Mu" / "Farewell, My Love...", because they use the same thread. */
	/* ######################### */

	/* San Fierro */
	offsetMap["GARAG1"] = 4928; // Wear Flowers In Your Hair
	debugCodeMap["GARAG1"] = true;

	offsetMap["DECON"] = 133; // Deconstruction
	debugCodeMap["DECON"] = true;

	offsetMap["SCRASH3"] = 679; // 555 WE TIP
	debugCodeMap["SCRASH3"] = true;

	offsetMap["SCRASH2"] = 661; // Snail Trail
	debugCodeMap["SCRASH2"] = true;

	offsetMap["WUZI1"] = 27975; // Mountain Cloud Boys

	offsetMap["FARLIE4"] = 608; // Ran Fa Li
	debugCodeMap["FARLIE4"] = true;

	offsetMap["DRIV6"] = 12781; // Lure
	offsetMap["WUZI2"] = 26588; // Amphibious Assault
	offsetMap["WUZI5"] = 20684; // The Da Nang Thang

	offsetMap["SYN1"] = 14568; // Photo Opportunity

	offsetMap["SYN2"] = 84; // Jizzy
	debugCodeMap["SYN2"] = true;

	offsetMap["SYN3"] = 19158; // Outrider
	offsetMap["SYND4"] = 12241; // Ice Cold Killa
	offsetMap["SYN6"] = 9169; // Toreno's Last Flight
	offsetMap["SYN7"] = 14730; // Yay Ka-Boom Boom
	offsetMap["SYN5"] = 23169; // Pier 69
	offsetMap["DRIV2"] = 12885; // T-Bone Mendez

	offsetMap["DRIV3"] = 2674; // Mike Toreno
	debugCodeMap["DRIV3"] = true;

	offsetMap["STEAL1"] = 7659; // Zeroing In
	offsetMap["STEAL2"] = 26031; // Test Drive

	offsetMap["STEAL4"] = 89; // Customs Fast Track
	debugCodeMap["STEAL4"] = true;

	offsetMap["STEAL5"] = 5117; // Puncture Wounds

	offsetMap["ZERO1"] = 5321; // Air Raid
	debugCodeMap["ZERO1"] = true;

	offsetMap["ZERO2"] = 3285; // Supply Lines...
	debugCodeMap["ZERO2"] = true;

	offsetMap["ZERO4"] = 2105; // New Model Army
	debugCodeMap["ZERO4"] = true;
	/* ######################### */

	/* Las Venturas */
	offsetMap["TORENO1"] = 14457; // Monster
	offsetMap["TORENO2"] = 10715; // Highjack

	offsetMap["DES3"] = 147; // Interdiction
	debugCodeMap["DES3"] = true;

	// offsetMap["DESERT4"] = 310; // Verdant Meadows - Cutscene?

	offsetMap["DESERT6"] = 726; // N.O.E.
	debugCodeMap["DESERT6"] = true;

	offsetMap["DESERT9"] = 21869; // Stowaway
	offsetMap["MAF4"] = 29924; // Black Project
	offsetMap["DES10"] = 4130; // Green Goo

	// offsetMap["DESERT5"] = -1; // Learning to Fly - TODO: Custom Handling somehow? Seems to crash with default debug method

	offsetMap["CASINO1"] = 19542; // Fender Ketchup
	offsetMap["CASINO2"] = 16387; // Explosive Situation
	offsetMap["CASINO3"] = 14129; // You've Had Your Chips
	// offsetMap["CASINO7"] = 319; // Fish in a Barrel - Cutscene?
	offsetMap["CASINO4"] = 45880; // Don Peyote
	offsetMap["CASINO5"] = 12838; // Intensive Care

	offsetMap["CASINO6"] = 1290; // The Meat Business
	debugCodeMap["CASINO6"] = true;

	offsetMap["CASINO9"] = 12440; // Freefall
	offsetMap["CASIN10"] = 15339; // Saint Mark's Bistro

	offsetMap["VCRASH1"] = 7980; // Misappropriation
	offsetMap["VCR2"] = 5058; // High Noon
	offsetMap["DOC2"] = 13233; // Madd Dogg

	offsetMap["HEIST1"] = 23694; // Architectural Espionage

	offsetMap["HEIST3"] = 2606; // Key To Her Heart
	debugCodeMap["HEIST3"] = true;

	offsetMap["HEIST2"] = 18813; // Dam And Blast
	offsetMap["HEIST4"] = 13180; // Cop Wheels
	offsetMap["HEIST5"] = 13735; // Up, Up and Away!
	offsetMap["HEIST9"] = 44516; // Breaking the Bank at Caligula's
	/* ######################### */

	/* Return To Los Santos */
	offsetMap["MANSIO1"] = 6889; // A Home In The Hills
	debugCodeMap["MANSIO1"] = true;

	offsetMap["MANSIO2"] = 1456; // Vertical Bird
	debugCodeMap["MANSIO2"] = true;

	offsetMap["MANSIO3"] = 6740; // Home Coming

	offsetMap["MANSON5"] = 1350; // Cut Throat Business
	debugCodeMap["MANSON5"] = true;

	offsetMap["GROVE1"] = 18881; // Beat Down on B Dup
	offsetMap["GROVE2"] = 3159; // Grove 4 Life

	offsetMap["RIOT1"] = 2997; // Riot
	offsetMap["RIOT2"] = 30259; // Los Desperados

	offsetMap["FINALEA"] = 1473; // End Of The Line (Part 1)
	debugCodeMap["FINALEA"] = true;

	offsetMap["FINALEB"] = -1; // End Of The Line (Part 2)
	debugCodeMap["FINALEB"] = true;

	offsetMap["FINALEC"] = 1817; // End Of The Line (Part 3)
	debugCodeMap["FINALEC"] = true;
	/* ######################### */
}

void PassMission::Disable() {
	isEnabled = false;

	TimedEffect::Disable();
}

void PassMission::HandleTick() {
	if (isEnabled) {
		missionPassWait -= CalculateTick();
		if (missionPassWait <= 0) {
			Disable();
		}
		return;
	}

	if (triedPassingMission || CCutsceneMgr::ms_running || FrontEndMenuManager.m_bWidescreenOn) {
		return;
	}

	for (auto i = CTheScripts::pActiveScripts; i; i = i->m_pNext) {
		if (i->m_bIsMission && i->m_bIsActive && !i->m_bIsExternal) {
			std::string missionName = GenericUtil::ToUpper(std::string(i->m_szName));
			if (offsetMap.contains(missionName)) {
				if (debugCodeMap.contains(missionName)) {
					isEnabled = true;
				}
				if (offsetMap[missionName] != -1) {
					i->m_pCurrentIP = i->m_pBaseIP + offsetMap[missionName];
				}

				ClearPlayerStatus();

				if (missionName == "SWEET1B") { // Cleaning The Hood
					CPed* player;
					Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR>(0, &player);
					if (player && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_3D>(player, 303.0f, 1112.0f, 1081.0f, 337.0f, 1133.0f, 1087.0f, 0)) {
						Teleportation::Teleport(CVector(2172.0f, -1677.0f, 16.0f));
					}
				}
				else if (missionName == "CRASH1") { // Burning Desire
					CPed* player;
					Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR>(0, &player);
					if (player && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_3D>(player, 2356.0f, -1191.0f, 1025.0f, 2316.0f, -1169.0f, 1039.0f, 0)) {
						Teleportation::Teleport(CVector(2351.0f, -1160.0f, 28.0f));
					}
				}
				else if (missionName == "MUSIC2") { // Madd Dogg's Rhymes
					CPed* player;
					Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR>(0, &player);
					if (player && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_3D>(player, 1304.0f, -841.0f, 1082.0f, 1219.0f, -748.0f, 1102.0f, 0)) {
						Teleportation::Teleport(CVector(1300.0f, -804.0f, 85.0f));
					}
				}
				else if (missionName == "CAT2") { // Small Town Bank
					CPed* player;
					Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR>(0, &player);
					if (player && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_2D>(player, 2302.0f, -19.0f, 2321.0f, 2.0f, 0)) {
						Teleportation::Teleport(CVector(2301.0f, -16.0f, 27.4f));
					}
				}
				else if (missionName == "GARAG1") { // Wear Flowers In Your Hair
					CPed* player;
					Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR>(0, &player);
					if (player) {
						Teleportation::Teleport(CVector(-2029.0f, 174.0f, 30.0f));
					}
				}
				else if (missionName == "CASINO3") { // You've Had Your Chips
					CPed* player;
					Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR>(0, &player);
					if (player && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_3D>(player, 1054.0f, 2074.0f, 8.0f, 1097.0f, 2148.0f, 22.0f, 0)) {
						Teleportation::Teleport(CVector(1051.0f, 2087.0f, 12.0f));
					}
				}
				else if (missionName == "MAF4") { // Black Project
					CPed* player;
					Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR>(0, &player);
					if (player && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_3D>(player, 182.0f, 1927.0f, 15.0f, 335.0f, 1767.0f, -42.0f, 0)) {
						Teleportation::Teleport(CVector(88.0f, 1921.0f, 19.0f));
					}
				}
				else if (missionName == "CASIN10") { // Saint Mark's Bistro
					CPed* player;
					Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR>(0, &player);
					if (player && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_3D>(player, -850.0f, 481.0f, 1349.0f, -777.0f, 543.0f, 1385.0f, 0)) {
						Teleportation::Teleport(CVector(1704.0f, 1447.0f, 12.0f));
					}
				}
				else if (missionName == "MANSIO1") { // A Home In The Hills
					CPed* player;
					Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR>(0, &player);
					if (player && player->GetPosition().z > 300.0f) {
						Teleportation::Teleport(CVector(1255.0f, -779.0f, 94.0f));
					}
				}
				else if (missionName == "FINALEB") { // End Of The Line (Part 2)
					CGame::currArea = 0;

					CEntryExitManager::ms_entryExitStackPosn = 0;
					CPopulation::bInPoliceStation = false;
					CStreaming::RemoveBuildingsNotInArea(0);

					CPed* player = FindPlayerPed();
					if (player) {
						player->m_nAreaCode = 0;
						player->m_pEnex = 0;
					}

					plugin::Call<0x40A560>(); // CStreaming::StreamZoneModels
					CTimeCycle::StopExtraColour(false);
				}

				else if (missionName == "FINALEC") { // End Of The Line (Part 3)
					Command<eScriptCommands::COMMAND_SET_LA_RIOTS>(0);
					Command<eScriptCommands::COMMAND_SET_CAR_DENSITY_MULTIPLIER>(1.0f);
					Command<eScriptCommands::COMMAND_SET_PED_DENSITY_MULTIPLIER>(1.0f);
				}

				return;
			}
			else if (missionName == "CPRACE") { // High Stakes, Low-Rider / Wu Zi Mu / Farewell, My Love...
				/*
				// TODO: Races are handled differently.
				// We need to increase global variables, which during initial testing didn't work as planned.

				int raceIndex = 0;
				Command<eScriptCommands::COMMAND_SET_LVAR_INT_TO_VAR_INT>(&raceIndex, CallMethodAndReturn<short, 0x464700, CRunningScript*>(i, 352));
				if (raceIndex == 0) { // High Stakes, Low-rider
					i->m_pCurrentIP = i->m_pBaseIP + 19649;
				}
				else if (raceIndex == 7) { // Wu Zi Mu
					int cesarPassed = 5, wuzimuStarted = 0;
					Command<eScriptCommands::COMMAND_SET_VAR_INT_TO_LVAR_INT>(CallMethodAndReturn<short, 0x464700, CRunningScript*>(i, 492), &cesarPassed);
					Command<eScriptCommands::COMMAND_SET_VAR_INT_TO_LVAR_INT>(CallMethodAndReturn<short, 0x464700, CRunningScript*>(i, 2196), &wuzimuStarted);

					Command<eScriptCommands::COMMAND_FAIL_CURRENT_MISSION>();
				}
				else if (raceIndex == 8) { // Farewell, My Love...
					int cesarPassed = 10, wuzimuStarted = 0;
					Command<eScriptCommands::COMMAND_SET_VAR_INT_TO_LVAR_INT>(CallMethodAndReturn<short, 0x464700, CRunningScript*>(i, 492), &cesarPassed);
					Command<eScriptCommands::COMMAND_SET_VAR_INT_TO_LVAR_INT>(CallMethodAndReturn<short, 0x464700, CRunningScript*>(i, 2196), &wuzimuStarted);

					Command<eScriptCommands::COMMAND_FAIL_CURRENT_MISSION>();
				}
				return;
				*/
			}
			else if (debugCodeMap.contains(missionName)) {
				isEnabled = true;
				return;
			}
		}
	}

	triedPassingMission = true;

	SetTextColor(false);
}

void PassMission::ClearPlayerStatus() {
	Player::RemoveBalaclava();

	CPed* player;
	Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR>(0, &player);
	if (player) {
		Command<eScriptCommands::COMMAND_SKIP_CUTSCENE_END>();
		Command<eScriptCommands::COMMAND_CLEAR_CHAR_TASKS>(player);
		Command<eScriptCommands::COMMAND_SET_CAMERA_BEHIND_PLAYER>();
		Command<eScriptCommands::COMMAND_SWITCH_WIDESCREEN>(0);
		Command<eScriptCommands::COMMAND_SET_PLAYER_CONTROL>(0, 1);
		Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT>();
		Command<eScriptCommands::COMMAND_DETACH_CHAR_FROM_CAR>(player);
	}
}

char __stdcall PassMission::HookedDebugGetKeyDown(int keyCode, int a2, int a3) {
	return isEnabled && keyCode == 83; // 83 / S for mission skip
}
