#pragma once

#include "common.h"
#include "plugin.h"

#include "CPlayerInfo.h"
#include "CTaskSimpleCarSetPedOut.h"
#include "CStats.h"

class Player
{
public:
	static void GivePlayerHealthArmorMoney();
	static void KillPlayer();

	static void KickOutOfVehicleAndLock();
	static void LockPlayerInsideVehicle();

	static void SetMaxStamina();
	static void SetMaxWeaponSkills();
	static void SetMaxDrivingSkills();

	static void DoWasted();
	static void DoBusted();
};

