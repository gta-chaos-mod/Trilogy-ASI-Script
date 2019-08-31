// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"
#include "plugin.h"

#include "CPlayerInfo.h"
#include "CStats.h"
#include "CTaskSimpleCarSetPedOut.h"

class Player
{
public:
	static void GivePlayerHealthArmorMoney();
	static void KillPlayer();

	static void KickOutOfVehicleAndLock();

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
};
