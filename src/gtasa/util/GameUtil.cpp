#include "GameUtil.h"

CPedAcquaintance GameUtil::backup_acquaintances[32];

std::string GameUtil::loadFilePath;
char* GameUtil::gamePath = reinterpret_cast<char*>(0xC92368);

std::string GameUtil::GetModVersion() {
	return "Chaos Mod v2.0.0";
}

CPedAcquaintance* GameUtil::GetPedTypeAcquaintances(int PedType) {
	return plugin::CallAndReturn<CPedAcquaintance*, 0x6089B0>(PedType);
}

void GameUtil::BackupAcquaintances() {
	SaveAcquaintances(backup_acquaintances);
}

void GameUtil::RestoreSavedAcquaintances() {
	LoadAcquaintances(backup_acquaintances);
}

CPedAcquaintance* GameUtil::GetSavedAcquaintance(int type) {
	if (type < 0 || type > 32) return nullptr;

	return &backup_acquaintances[type];
}

void GameUtil::SaveAcquaintances(CPedAcquaintance* acquaintances) {
	for (int i = 0; i < 32; i++) {
		memcpy(&acquaintances[i], GetPedTypeAcquaintances(i), sizeof(CPedAcquaintance));
	}
}

void GameUtil::LoadAcquaintances(CPedAcquaintance* acquaintances) {
	for (int i = 0; i < 32; i++) {
		memcpy(GetPedTypeAcquaintances(i), &acquaintances[i], sizeof(CPedAcquaintance));
	}
}

void GameUtil::DeleteAutosave() {
	std::sprintf(CGenericGameStorage::ms_ValidSaveName, "%s\\chaos_mod\\chaos_autosave.b", gamePath);

	if (std::filesystem::exists(CGenericGameStorage::ms_ValidSaveName)) {
		std::filesystem::remove(CGenericGameStorage::ms_ValidSaveName);
	}
}

void GameUtil::SaveToFile(std::string fileName) {
	std::sprintf(CGenericGameStorage::ms_ValidSaveName, "%s\\%s", gamePath, fileName.c_str());

	std::filesystem::path p(CGenericGameStorage::ms_ValidSaveName);
	std::filesystem::create_directories(p.parent_path());

	// Temporarily disable cheats and certain effects so they don't get saved
	for (int i = 0; i < 92; i++) {
		CCheat::m_aCheatsActive[i] = false;
	}
	CClock::ms_nMillisecondsPerGameMinute = 1000;

	CPlayerPed* player = FindPlayerPed();
	int tempMoney = -1;
	if (player) {
		tempMoney = LongLiveTheRichEffect::isEnabled ? LongLiveTheRichEffect::storedMoney : player->GetPlayerInfoForThisPlayerPed()->m_nMoney;
	}

	player->GetPlayerInfoForThisPlayerPed()->m_nMoney = tempMoney;

	CPedAcquaintance temp_acquaintances[32];
	SaveAcquaintances(temp_acquaintances);
	RestoreSavedAcquaintances();

	CGenericGameStorage::GenericSave(0);

	LoadAcquaintances(temp_acquaintances);

	if (player) {
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney = LongLiveTheRichEffect::isEnabled ? (int)LongLiveTheRichEffect::gainedMoney : tempMoney;
	}
}

bool GameUtil::LoadFromFile(std::string fileName) {
	std::sprintf(CGenericGameStorage::ms_LoadFileName, "%s\\%s", gamePath, fileName.c_str());

	if (std::filesystem::exists(CGenericGameStorage::ms_LoadFileName)) {
		FrontEndMenuManager.m_bLoadingData = true;
		FrontEndMenuManager.m_bMenuActive = false;

		byte gameState = injector::ReadMemory<byte>(0xC8D4C0); // GameState

		if (gameState == 9) {
			CGame::ShutDownForRestart();
			CGame::InitialiseWhenRestarting();
		}

		return true;
	}

	return false;
}

std::string GameUtil::GetLoadFileName() {
	return loadFilePath;
}

void GameUtil::SetVehiclesToRealPhysics() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_pDriver
			&& vehicle->CanBeDriven()
			&& vehicle->m_nStatus != eEntityStatus::STATUS_WRECKED
			&& vehicle->m_nStatus != eEntityStatus::STATUS_PHYSICS
			&& !vehicle->IsDriver(FindPlayerPed())
			) {
			CCarCtrl::SwitchVehicleToRealPhysics(vehicle);
		}
	}
}

void GameUtil::RemovePlayerBalaclava() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		CPedClothesDesc* clothes = player->m_pPlayerData->m_pPedClothesDesc;
		if (clothes && clothes->GetIsWearingBalaclava()) {
			clothes->SetTextureAndModel((unsigned int)0, (unsigned int)0, 17);
			RebuildPlayer();
		}
	}
}

void GameUtil::RebuildPlayer() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		ePedState oldState = player->m_nPedState;
		player->m_nPedState = ePedState::PEDSTATE_IDLE;
		CClothes::RebuildPlayer(player, false);
		player->m_nPedState = oldState;
	}
}

float GameUtil::GetAudioVolumeOrOverride(float volume) {
	if (Config::GetOrDefault("Fixes.DisableRadioWhenNormalSpeed", false)) {
		volume = -100.0f;
	}

	return volume;
}

int GameUtil::GetRealMissionsPassed() {
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
