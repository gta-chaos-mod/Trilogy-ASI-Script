// Copyright (c) 2019 Lordmau5
#include "GenericUtil.h"

std::vector<std::string> GenericUtil::replacements;
bool GenericUtil::areEffectsCryptic = false;
CPedAcquaintance GenericUtil::backup_acquaintances[32];

void GenericUtil::InitializeUnprotectedMemory() {
	DWORD ignore;
	injector::UnprotectMemory(0x863984, sizeof(GAME_GRAVITY), ignore);
}

void GenericUtil::InitializeCharReplacements() {
	// Lower-case a-z
	replacements.push_back("abcdefghijklmnopqrstuvwxyz");

	// Upper-case A-Z
	replacements.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	// Numbers 0-9
	replacements.push_back("0123456789");

	// Symbols
	replacements.push_back("!?\"$%&(),.=+-_*/");
}

std::vector<std::string> GenericUtil::GetCharReplacements() {
	return replacements;
}

int GenericUtil::GetRealMissionsPassed() {
	int passed = 0;

	// Los Santos
	passed += injector::ReadMemory<byte>(0xA4A060); // Intro
	passed += injector::ReadMemory<byte>(0xA4A070); // Sweet
	passed += injector::ReadMemory<byte>(0xA4A07C); // OG Loc
	passed += injector::ReadMemory<byte>(0xA4A080); // Crash
	passed += injector::ReadMemory<byte>(0xA4A074); // Ryder
	passed += injector::ReadMemory<byte>(0xA4A078); // Smoke
	passed += injector::ReadMemory<byte>(0xA4A084); // Lowrider
	passed += injector::ReadMemory<byte>(0xA4A088); // LS Final

	// Badlands
	passed += injector::ReadMemory<byte>(0xA4A114); // Badlands
	passed += injector::ReadMemory<byte>(0xA4A10C); // The Truth
	passed += injector::ReadMemory<byte>(0xA4A110) / 5; // Cesar (both races increase throughout the race - we are interested in 5 and 10)
	passed += injector::ReadMemory<byte>(0xA4A488); // Catalina (Local Liquor Store)
	passed += injector::ReadMemory<byte>(0xA4A48C); // Catalina (Small Town Bank)
	passed += injector::ReadMemory<byte>(0xA4A490); // Catalina (Tanker Commander)
	passed += injector::ReadMemory<byte>(0xA4A494); // Catalina (Against All Odds)
	passed += injector::ReadMemory<byte>(0xA4BB2C); // King in Exile

	// San Fierro
	passed += injector::ReadMemory<byte>(0xA4A1D4); // Garage
	passed += injector::ReadMemory<byte>(0xA4A1DC); // Wuzimu
	passed += injector::ReadMemory<byte>(0xA4A1E4); // Syndicate
	passed += injector::ReadMemory<byte>(0xA4A1E8); // Crash
	passed += injector::ReadMemory<byte>(0xA4A1D8); // Zero
	passed += injector::ReadMemory<byte>(0xA4A1E0); // Steal

	// Las Venturas
	passed += injector::ReadMemory<byte>(0xA4A2A4); // Toreno
	passed += injector::ReadMemory<byte>(0xA4A2B4); // Casino
	passed += injector::ReadMemory<byte>(0xA4A2B8); // Crash
	passed += injector::ReadMemory<byte>(0xA4A2BC); // Madd Dogg
	passed += injector::ReadMemory<byte>(0xA4A2C0); // Heist

	// Return to Los Santos
	passed += injector::ReadMemory<byte>(0xA4A328); // Mansion
	passed += injector::ReadMemory<byte>(0xA4A32C); // Grove
	passed += injector::ReadMemory<byte>(0xA4A334); // Riot

	return passed;
}

CPedAcquaintance* GenericUtil::GetPedTypeAcquaintances(int PedType) {
	return plugin::CallAndReturn<CPedAcquaintance*, 0x6089B0>(PedType);
}

void GenericUtil::BackupAcquaintances() {
	SaveAcquaintances(backup_acquaintances);
}

void GenericUtil::RestoreSavedAcquaintances() {
	LoadAcquaintances(backup_acquaintances);
}

void GenericUtil::SaveAcquaintances(CPedAcquaintance* acquaintances) {
	for (int i = 0; i < 32; i++) {
		memcpy(&acquaintances[i], GetPedTypeAcquaintances(i), sizeof(CPedAcquaintance));
	}
}

void GenericUtil::LoadAcquaintances(CPedAcquaintance* acquaintances) {
	for (int i = 0; i < 32; i++) {
		memcpy(GetPedTypeAcquaintances(i), &acquaintances[i], sizeof(CPedAcquaintance));
	}
}
