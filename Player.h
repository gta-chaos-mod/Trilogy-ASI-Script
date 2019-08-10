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
	static void LockPlayerInsideVehicle();

	static void SetStamina(bool isMax);
	static void SetWeaponSkills(bool isMax);
	static void SetDrivingSkills(bool isMax);

	static void DoWasted();
	static void DoBusted();
};
