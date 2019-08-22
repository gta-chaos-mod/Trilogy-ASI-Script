// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"

class GenericUtil
{
private:
	static std::vector<std::string> replacements;

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
};
