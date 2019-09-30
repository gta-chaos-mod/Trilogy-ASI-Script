// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"
#include "plugin.h"

#include "CClothes.h"
#include "CPlayerInfo.h"
#include "CStats.h"
#include "CStreaming.h"
#include "CTaskSimpleCarSetPedOut.h"

#include "CTheScripts.h"
#include "extensions/ScriptCommands.h"

class Player
{
public:
	static void GivePlayerHealthArmorMoney();
	static void KillPlayer();
	static void WeaponSet4();

	static void KickOutOfVehicleAndLock();

	static void MakeFat();
	static void MakeMuscle();
	static void MakeSkinny();

	static void SetStamina(bool isMax);
	static void NoStamina();
	static void MaxStamina();

	static void SetWeaponSkills(bool isMax);
	static void NoWeaponSkills();
	static void MaxWeaponSkills();

	static void SetDrivingSkills(bool isMax);
	static void NoDrivingSkills();
	static void MaxDrivingSkills();

	static void DoWasted();
	static void DoBusted();

	static void RemoveBalaclava();
	static void RebuildPlayer();
};
