// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"

#include <filesystem>

#include "CCheat.h"
#include "CClock.h"
#include "CGame.h"
#include "CGenericGameStorage.h"
#include "CMenuManager.h"

class GenericUtil
{
private:
	static std::vector<std::string> replacements;
	static std::string loadFilePath;
	static char* gamePath;

public:
	static bool areEffectsCryptic;

	static CPedAcquaintance backup_acquaintances[32];

public:
	static void InitializeUnprotectedMemory();
	static void InitializeCharReplacements();

	static std::vector<std::string> GetCharReplacements();

	static int GetRealMissionsPassed();

	static CPedAcquaintance* GetPedTypeAcquaintances(int PedType);
	static void BackupAcquaintances();
	static void RestoreSavedAcquaintances();
	static void SaveAcquaintances(CPedAcquaintance* acquaintances);
	static void LoadAcquaintances(CPedAcquaintance* acquaintances);

	static void SaveToFile(std::string fileName);
	static bool LoadFromFile(std::string fileName);
	static std::string GetLoadFileName();

	static int CalculateTick();
};
